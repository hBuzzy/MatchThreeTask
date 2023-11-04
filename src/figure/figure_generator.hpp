#ifndef FIGURE_GENERATOR_HPP
#define FIGURE_GENERATOR_HPP

#include <QObject>
#include <QColor>
#include <QVarLengthArray>

#include <random>
#include <concepts>
#include <execution>

#include "figure.hpp"

template <std::uniform_random_bit_generator RandGen = std::mt19937, std::size_t c = 7>
class FigureGenerator final {
public:
    explicit FigureGenerator(
        RandGen&& randGen = std::mt19937{std::random_device{}()},
        const QVarLengthArray<QColor, c>& colors = {
            {236, 39, 51}, // Red
            {246, 149, 34}, // Orange
            {251, 224, 0}, // Yellow
            {78, 182, 72}, // Green
            {43, 171, 225}, // Light blue
            {0, 90, 156}, // Dark blue
            {145, 43, 139} // Purple
        }
    ) : randGen_{std::forward<RandGen>(randGen)}, colors_(colors) {};
public:
    [[nodiscard]] QVarLengthArray<QColor, 4> GenerateColors() {
        return {
            colors_[randGen_() % c],
            colors_[randGen_() % c],
            colors_[randGen_() % c],
            colors_[randGen_() % c],
        };
    };
    [[nodiscard]] Figure operator()() {
        return { randGen_() % 5, randGen_() % 4, GenerateColors() };
    };
private:
    RandGen randGen_;
    const QVarLengthArray<QColor, c> colors_;
};

template <std::uniform_random_bit_generator RandGen, std::size_t c>
FigureGenerator(RandGen&&, const QVarLengthArray<QColor, c>&) -> FigureGenerator<RandGen, c>;

#endif
