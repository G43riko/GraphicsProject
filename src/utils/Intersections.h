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
bool intersectRayWithSquare(Vector3f R1, Vector3f R2, Vector3f S1, Vector3f S2, Vector3f S3) {
    // 1.
    Vector3f dS21 = S2 - S1;
    Vector3f dS31 = S3 - S1;
    Vector3f n = dS21.getCross(&dS31);
    // 2.
    Vector3f dR = R1 - R2;
    float ndotdR = n.dot(&dR);

    if (ABS(ndotdR) < 1e-6f) { // Choose your tolerance
        return false;
    }
    float t = -n.dot(R1 - S1) / ndotdR;
    Vector3f M = R1 + (dR * t);

    // 3.
    Vector3f dMS1 = M - S1;
    float u = dMS1.dot(&dS21);
    float v = dMS1.dot(&dS31);

    // 4.
    return (u >= 0.0f && u <= dS21.dot(&dS21) && v >= 0.0f && v <= dS31.dot(&dS31));
}
#endif //GAMEENGINE_INTERSECTIONS_H
