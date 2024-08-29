class HiroPoint {
public:
  HiroPoint() : m_x(0), m_y(0) {}
  HiroPoint(i32 x, i32 y) : m_x(x), m_y(y) {}

  auto x() const -> i32 { return m_x; }
  auto y() const -> i32 { return m_y; }
  auto x(i32 x) -> void { m_x = x; }
  auto y(i32 y) -> void { m_y = y; }

  auto operator=(const HiroPoint &point) -> HiroPoint& {
    m_x = point.m_x;
    m_y = point.m_y;
    return *this;
  }

private:
  i32 m_x;
  i32 m_y;
};
