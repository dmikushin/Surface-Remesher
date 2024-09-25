// MIT License
//
// Copyright(c) 2020 Zheng Jiaqi @NUSComputing
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "surfremesh.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;
using json = nlohmann::json;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <surface_mesh.off|surface_mesh.json>\n";
        return 0;
    }

    fs::path inputPath = argv[1];
    if (!fs::exists(inputPath))
    {
        std::cerr << "File does not exist: " << inputPath << "\n";
        return 1;
    }

    double edge_length_limit = 0.72;
    int imageSize = 2048;
    int depth = 1;
    int maxIter = 1000;
    int vertices = 20000;

    std::string inputMeshFname;
    std::string outputMeshFname;
    std::string seamsFname;
    std::string parameterizationFname;

    if (inputPath.extension() == ".json")
    {
        std::ifstream jsonFile(inputPath);
        if (!jsonFile)
        {
            std::cerr << "Failed to open JSON file: " << inputPath << "\n";
            return 1;
        }

        json j;
        jsonFile >> j;

        inputMeshFname = j.at("inputMeshFname").get<std::string>();
        outputMeshFname = j.value("outputMeshFname", inputMeshFname + ".result.off");
        seamsFname = j.value("seamsFname", inputMeshFname + ".selection.txt");
        parameterizationFname = j.value("parameterizationFname", inputMeshFname + ".parameterization.off");
        edge_length_limit = j.value("edge_length_limit", edge_length_limit);
        imageSize = j.value("imageSize", imageSize);
        depth = j.value("depth", depth);
        maxIter = j.value("maxIter", maxIter);
        vertices = j.value("vertices", vertices);
    }
    else if (inputPath.extension() == ".off")
    {
        inputMeshFname = inputPath.string();
        outputMeshFname = inputMeshFname + ".result.off";
        seamsFname = inputMeshFname + ".selection.txt";
        parameterizationFname = inputMeshFname + ".parameterization.off";
    }
    else
    {
        std::cerr << "Unsupported file extension: " << inputPath.extension() << "\n";
        return 1;
    }

    return surfremesh(inputMeshFname, outputMeshFname, seamsFname, parameterizationFname, edge_length_limit, imageSize, depth, maxIter, vertices);
}
