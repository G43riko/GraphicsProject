//
// Created by gabriel on 17.4.2017.
//

#ifndef GAMEENGINE_INTERSECTIONS_H
#define GAMEENGINE_INTERSECTIONS_H

#include <src/utils/Vectors.h>

/**
 * 1. The normal to the plane is: n = (S2 - S1) x (S3 - S1)
 *  A point M belongs to this plane iff it satisfies this equation: n . ( M - S1 ) = 0
 *
 * 2. A point M belongs to the ray iff it can be written: M = R1 + t * dR with dR = R2 - R1
 *  Compute the ray / plane intersection (equate the two previous equations):
 *  n . ( M - S1 ) = 0 = n . ( R1 + t * dR - S1 ) = n . (R1 - S1) + t * n . dR
 *  If n . dR is 0 then the plane is parallel to the ray, and there is no intersection (again, ignoring the case where the ray is embedded in the plane).
 *  Else t = -n . (R1 - S1) / n . dR and plugging this result into the previous equation M = R1 + t * dR gives the 3D coordinates of the point of intersection M.
 *
 * 3. Project the vector M - S1 onto the two vectors S2 - S1 and S3 - S1 (the square edges starting from S1), this gives two numbers (u, v):
 *  u = (M - S1) . (S2 - S1)
 *  v = (M - S1) . (S3 - S1)
 *
 * 4. If 0 <= u <= |S2 - S1|^2 and 0 <= v <= |S3 - S1|^2, then the point of intersection M lies inside the square, else it's outside.
 *
 * @param R1
 * @param R2
 * @param S1
 * @param S2
 * @param S3
 * @return
 */
bool intersectRayWithSquare(const Vector3f R1, const Vector3f R2, const Vector3f S1, const Vector3f S2, const Vector3f S3) {
    // 1.
    Vector3f dS21 = S2 - S1;
    Vector3f dS31 = S3 - S1;
    Vector3f n = dS21.getCross(dS31);
    // 2.
    Vector3f dR = R1 - R2;
    float ndotdR = n.dot(dR);

    if (ABS(ndotdR) < 1e-6f) { // Choose your tolerance
        return false;
    }
    float t = -n.dot(R1 - S1) / ndotdR;
    Vector3f M = R1 + (dR * t);

    // 3.
    Vector3f dMS1 = M - S1;
    float u = dMS1.dot(dS21);
    float v = dMS1.dot(dS31);

    // 4.
    return (u >= 0.0f && u <= dS21.dot(dS21) && v >= 0.0f && v <= dS31.dot(dS31));
}
/////////////
float mod(const float value, const float modulus) {
    return fmodf((fmodf(value, modulus) + modulus), modulus);
}
float intbound(const float s, const float ds) {
    // Find the smallest positive t such that s+t*ds is an integer.
    if (ds < 0) {
        return intbound(-s, -ds);
    } else {
        // problem is now s+t*ds = 1
        return (1 - mod(s, 1)) / ds;
    }
}

/**
 * AK vráti true tak sa prestane prehladávať dalej
 *
 * @param x
 * @param y
 * @param z
 * @param face
 * @return
 */
bool callback(const int x, const int y, const int z, const Vector3f face){
    PRINT("kolizia: [" << x << ", " << y << ", " << z << "]\nface: ");
    face.show();

    return false;
}

void raycast(const Vector3f origin, const Vector3f direction, float radius = 100) {
    // From "A Fast Voxel Traversal Algorithm for Ray Tracing"
    // by John Amanatides and Andrew Woo, 1987
    // <http://www.cse.yorku.ca/~amana/research/grid.pdf>
    // <http://citeseer.ist.psu.edu/viewdoc/summary?doi=10.1.1.42.3443>
    // Extensions to the described algorithm:
    //   • Imposed a distance limit.
    //   • The face passed through to reach the current cube is provided to
    //     the callback.

    // The foundation of this algorithm is a parameterized representation of
    // the provided ray,
    //                    origin + t * direction,
    // except that t is not actually stored; rather, at any given point in the
    // traversal, we keep track of the *greater* t values which we would have
    // if we took a step sufficient to cross a cube boundary along that axis
    // (i.e. change the integer part of the coordinate) in the variables
    // tMaxX, tMaxY, and tMaxZ.

    // Cube containing origin point.
    int x = (int)floor(origin.x);
    int y = (int)floor(origin.y);
    int z = (int)floor(origin.z);
    // Break out direction vector.
    float dx = direction.x;
    float dy = direction.y;
    float dz = direction.z;
    // Direction to increment x,y,z when stepping.
    float stepX = SIGNUM(dx);
    float stepY = SIGNUM(dy);
    float stepZ = SIGNUM(dz);
    // See description above. The initial values depend on the fractional
    // part of the origin.
    float tMaxX = intbound(origin.x, dx);
    float tMaxY = intbound(origin.y, dy);
    float tMaxZ = intbound(origin.z, dz);
    // The change in t when taking a step (always positive).
    float tDeltaX = stepX / dx;
    float tDeltaY = stepY / dy;
    float tDeltaZ = stepZ / dz;
    // Buffer for reporting faces to the callback.
    Vector3f face;

    // Avoids an infinite loop.
    if (EZ(dx) && EZ(dy) && EZ(dz)){
        return;
        //throw new RangeError("Raycast in zero direction!");
    }

    // Rescale from units of 1 cube-edge to units of 'direction' so we can
    // compare with 't'.
    radius /= (float)sqrt(dx * dx + dy * dy + dz * dz);

    int wx = 1000;
    int wy = 1000;
    int wz = 1000;

    while (/* ray has not gone past bounds of world */
            (stepX > 0 ? x < wx : x >= 0) &&
            (stepY > 0 ? y < wy : y >= 0) &&
            (stepZ > 0 ? z < wz : z >= 0)) {

        // Invoke the callback, unless we are not *yet* within the bounds of the
        // world.
        if (!(x < 0 || y < 0 || z < 0 || x >= wx || y >= wy || z >= wz))
            if (callback(x, y, z, face))
                break;

        // tMaxX stores the t-value at which we cross a cube boundary along the
        // X axis, and similarly for Y and Z. Therefore, choosing the least tMax
        // chooses the closest cube boundary. Only the first case of the four
        // has been commented in detail.
        if (tMaxX < tMaxY) {
            if (tMaxX < tMaxZ) {
                if (tMaxX > radius) break;
                // Update which cube we are now in.
                x += (int)stepX;
                // Adjust tMaxX to the next X-oriented boundary crossing.
                tMaxX += tDeltaX;
                // Record the normal vector of the cube face we entered.
                face.x = -stepX;
                face.y = 0;
                face.z = 0;
            } else {
                if (tMaxZ > radius) break;
                z += (int)stepZ;
                tMaxZ += tDeltaZ;
                face.x = 0;
                face.y = 0;
                face.z = -stepZ;
            }
        } else {
            if (tMaxY < tMaxZ) {
                if (tMaxY > radius) break;
                y += (int)stepY;
                tMaxY += tDeltaY;
                face.x = 0;
                face.y = -stepY;
                face.z = 0;
            } else {
                // Identical to the second case, repeated for simplicity in
                // the conditionals.
                if (tMaxZ > radius) break;
                z += (int)stepZ;
                tMaxZ += tDeltaZ;
                face.x = 0;
                face.y = 0;
                face.z = -stepZ;
            }
        }
    }
}
#endif //GAMEENGINE_INTERSECTIONS_H
