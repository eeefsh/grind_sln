#pragma once

#include"manager_h/xt_armadillo_settings.h"
#include"cereal/include/cereal/cereal.hpp"
#include"cereal/include/cereal/archives/binary.hpp"
#include"cereal/include/cereal/types/vector.hpp"
#include <iostream>
#include<vector>
namespace cereal {

    // Armadillo矩阵序列化特化
    template <class Archive>
    void serialize(Archive& ar, arma::mat& m) {
        // 确保矩阵内存连续
        //if (!m.is_contiguous()) {
        //    throw std::runtime_error("非连续矩阵需要特殊处理");
        //}

        arma::uword rows, cols;
        if constexpr (Archive::is_loading::value) {
            ar(rows, cols);
            m.set_size(rows, cols);
        }
        else {
            rows = m.n_rows;
            cols = m.n_cols;
            ar(rows, cols);
        }
        ar(cereal::binary_data(m.memptr(), rows * cols * sizeof(double)));
    }

} // namespace cereal

namespace cereal {
    template <typename Archive, typename T>
    void save(Archive& ar, const std::queue<T>& queue) {
        // 将queue转换为vector序列化
        std::vector<T> temp_vec;
        auto q = queue; // 拷贝队列，避免修改原队列
        while (!q.empty()) {
            temp_vec.push_back(q.front());
            q.pop();
        }
        ar(temp_vec);
    }

    template <typename Archive, typename T>
    void load(Archive& ar, std::queue<T>& queue) {
        // 从vector加载到queue
        std::vector<T> temp_vec;
        ar(temp_vec);
        // 清空原始队列
        while (!queue.empty()) queue.pop();
        // 从vector填充队列
        for (const auto& item : temp_vec) {
            queue.push(item);
        }
    }
}