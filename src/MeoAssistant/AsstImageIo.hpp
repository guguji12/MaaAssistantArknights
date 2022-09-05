#pragma once

#include <string>
#include <vector>
#include <filesystem>

#include "NoWarningCVMat.h"
#include "NoWarningCV.h"

#include "AsstUtils.hpp"

namespace asst {

    inline cv::Mat imread(const std::filesystem::path& path, int flags = cv::IMREAD_COLOR)
    {
        std::ifstream file(path, std::ios::binary | std::ios::ate);
        auto fileSize = file.tellg();
        file.seekg(0, std::ios::beg);
        std::vector<uint8_t> content(fileSize);
        file.read((char*)&content[0], fileSize);
        return cv::imdecode(content, flags);
    }

    inline cv::Mat imread(const std::string& utf8_path, int flags = cv::IMREAD_COLOR) {
        return imread(asst::utils::path(utf8_path), flags);
    }

    inline bool imwrite(const std::filesystem::path& path, cv::InputArray img, const std::vector<int>& params = std::vector<int>()) {
        std::ofstream of(path, std::ios::out | std::ios::binary);
        std::vector<uint8_t> encoded;
        auto ext = asst::utils::path_to_utf8_string(path.extension());
        if (cv::imencode(ext.c_str(), img, encoded, params)) {
            of.write((char*)&encoded[0], encoded.size());
            return true;
        }
        return false;
    }

    inline bool imwrite(const std::string& utf8_path, cv::InputArray img, const std::vector<int>& params = std::vector<int>()) {
        return imwrite(asst::utils::path(utf8_path), img, params);
    }

}
