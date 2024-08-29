class HiroRect {
public:
  HiroRect() : m_x(0), m_y(0), m_width(0), m_height(0) {}
  HiroRect(i32 x, i32 y, i32 w, i32 h) : m_x(x), m_y(y), m_width(w), m_height(h) {}

  auto x() const -> i32 { return m_x; }
  auto y() const -> i32 { return m_y; }
  auto width()  const -> i32 { return m_width; }
  auto height() const -> i32 { return m_height; }

  auto x(i32 x) -> void { m_x = x; }
  auto y(i32 y) -> void { m_y = y; }
  auto width(i32 w)  -> void { m_width = w; }
  auto height(i32 h) -> void { m_height = h; }

  auto operator=(const HiroRect &rect) -> HiroRect& {
    m_x = rect.m_x;

    m_y = rect.y();
    m_width = rect.width();
    m_height = rect.height();
    return *this;
  }

private:
  i32 m_x;
  i32 m_y;
  i32 m_width;
  i32 m_height;
};
