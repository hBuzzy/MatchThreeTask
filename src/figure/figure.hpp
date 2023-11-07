#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <QObject>
#include <QColor>
#include <QVarLengthArray>

#include <random>
#include <concepts>
#include <ranges>

class Figure final {
public:
    using pos_t = QVarLengthArray<QVarLengthArray<uint, 3>, 4>;
public:
    Figure() = default;
    Figure(uint preset, uint rotation, const QVarLengthArray<QColor, 4>& colors)
    : preset_(preset), rotation_(rotation), colors_(colors) {};
public:
    [[nodiscard]] Figure Rotated() const {
        return { preset_, (rotation_ + 1) % 4, colors_ };
    }
    void Rotate() {
        rotation_ = (rotation_ + 1) % 4;
    }
    [[nodiscard]] auto GetGeometry() const {
        return presets_[preset_][rotation_];
    }
    [[nodiscard]] auto GetColors() const {
        return colors_;
    }
    void SetColors(const QVarLengthArray<QColor, 4>& colors) {
        colors_ = colors;
    }
    [[nodiscard]] uint GetLeft() const {
        return std::ranges::min(
            presets_[preset_][rotation_], {},
            [](auto&& arg) { return std::forward<decltype(arg)>(arg)[1]; }
        )[1];
    }
    [[nodiscard]] uint GetRight() const {
        return std::ranges::max(
            presets_[preset_][rotation_], {},
            [](auto&& arg) { return std::forward<decltype(arg)>(arg)[1]; }
        )[1];
    }
    [[nodiscard]] uint GetTop() const {
        return std::ranges::min(
            presets_[preset_][rotation_], {},
            [](auto&& arg) { return std::forward<decltype(arg)>(arg)[0]; }
        )[0];
    }
    [[nodiscard]] uint GetBottom() const {
        return std::ranges::max(
            presets_[preset_][rotation_], {},
            [](auto&& arg) { return std::forward<decltype(arg)>(arg)[0]; }
        )[0];
    }
private:
    static const QVarLengthArray<QVarLengthArray<pos_t, 4>, 5> presets_;
    uint preset_ = 0, rotation_ = 0;
    QVarLengthArray<QColor, 4> colors_;
};

#endif
