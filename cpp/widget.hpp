class Widget;
using WidgetList = std::vector<Widget *>;

struct Widget {
  virtual ~Widget();

  virtual auto initialize(Widget *parent) -> bool;
  virtual auto shutdown() -> void;

#if 0
  inline int getIndexInParent() const { return mIndexInParent; }
  inline void setIndexInParent(int index) { mIndexInParent = index; }

  void setParent(Widget *parent);
  Widget *getParent();
  bool removeChild(Widget *widget);
  void reverseChild();
  void removeAllChild();
  void fall();
  void rise();

  inline int width() { return m_rect.width(); }
  inline int height() { return m_rect.height(); }
  inline int x() { return m_rect.x(); }
  inline int y() { return m_rect.y(); }
  inline const HiroRect &geometry() const { return m_rect; }
  HiroRect globalGeometry() const;
  inline const HiroRect &validRect() const { return m_valid_rect; }
  virtual void move(int x, int y);
  void resize(int w, int h);
  void updateValid();
  void updateOffset();
  inline bool isVisible() const { return m_visible; }
  inline bool isHidden() const { return !m_visible; }
  inline const HiroPoint &offset() { return m_offset; }
  inline void setOffset(int x, int y) { m_offset.x(x), m_offset.y(y); }
  virtual void show();
  virtual void hide();
  virtual bool isDirty() const { return m_dirty; }
  virtual void update();
  inline unsigned int winID() const { return m_win_id; }
  bool isFocusIn();
  inline void enableFocus(bool b) { mEnableFocus = b; }
  inline const bool &isFocusEnabled() { return mEnableFocus; }
  virtual bool setFocus(bool focus);
  void setChildFocus(Widget *child);
  void SetHasGameList(int flag) {
    this->mIsGameList = flag;
  }
  void setLeftFocus(Widget *widget);
  void setRightFocus(Widget *widget);
  void setUpFocus(Widget *widget);
  void clearUpFocus();
  void setDownFocus(Widget *widget);
  virtual bool focusLeft();
  virtual bool focusRight();
  virtual bool focusUp();
  virtual bool focusDown();
  virtual void focusIn(HiroRect r);
  virtual void focusOut();
#endif

protected:
  u64        m_win_id     = 0;
  HiroPoint  m_offset     = {};
  HiroRect   m_rect       = {};
  HiroRect   m_valid_rect = {};
  bool       m_visible    = false;
  bool       m_is_hided   = false;
  bool       m_dirty       = false;
  Widget    *m_parent     = nullptr;
  WidgetList m_children   = {};

#if 0
  void releaseAllChild();
  virtual bool addChild(Widget *child);
  virtual bool addChildToPositon(Widget *child, unsigned int pos);
  void updateValidRect(const HiroRect &rect, HiroRect &validRect);
  virtual void onValidChanged();
  virtual void onOffsetChanged();
  virtual void onConfigurationChanged(int changed);
  virtual void onShow();
  virtual void onHide();
  virtual void onFocusIn(HiroRect r);
  virtual void onFocusOut();
  virtual bool click();
  virtual bool onClick();
  virtual bool back();
  virtual bool onBack();
  //-------------------- attach ------------
  virtual void onAttach();
  virtual void onDettach();
  virtual void onDraw();
  /*******************************zb***************************/
  virtual int getImageW();
  virtual void ScalImage(int w);
  virtual void ResetImage() {}
  virtual void ResetImageScale(int w) {}
  virtual void recthide(int flag) {}
  virtual void rectshow(int flag) {}
  /*******************************zb***************************/

  Widget *mLeftFocus;
  Widget *mRightFocus;
  Widget *mUpFocus;
  Widget *mDownFocus;
  Widget *mFocusChild;

  bool hasFocus;
  bool mEnableFocus;
  int mIndexInParent;

  void draw();
  bool isParentDirty();
  //-------------------- attach ------------
  void attach();
  void dettach();
#endif
};
