#ifndef SURFREMESH_H
#define SURFREMESH_H

#include <string>

int surfremesh(const std::string &inputMeshFname,
               const std::string &outputMeshFname,
               const std::string &seamsFname,
               const std::string &parameterizationFname,
               double edge_length_limit = 0.72,
               int imageSize = 2048,
               int depth = 1,
               int maxIter = 1000,
               int vertices = 20000);

#endif // SURFREMESH_H
