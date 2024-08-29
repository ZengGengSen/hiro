static u64 get_win_id() {
  static std::atomic<u64> id{0};
  return ++id;
}

Widget::~Widget() {
  shutdown();
}

auto Widget::initialize(Widget *parent) -> bool {
  m_win_id = get_win_id();
  m_offset = {};
  m_rect = {};
  m_valid_rect = {};
  m_visible = false;
  m_is_hided = false;
  m_dirty = false;
  m_parent = parent;
  m_children = {};
  return true;
}

auto Widget::shutdown() -> void {
  for (auto &child : m_children) {
    child->shutdown();
    delete child;
  }
 
  m_win_id = 0;
  m_offset = {};
  m_rect = {};
  m_valid_rect = {};
  m_visible = false;
  m_is_hided = false;
  m_dirty = false;
  m_parent = nullptr;
  m_children = {};
}

#if 0
void Widget::releaseAllChild() {
  if (m_children != NULL) {
    for (unsigned i = 0; i < m_children->size(); ++i)
      delete m_children->at(i);

    delete m_children;
    m_children = NULL;
  }

  mFocusChild = NULL;
}

HiroRect Widget::globalGeometry() const {
  if (m_parent == NULL)
    return m_rect;
  else {
    HiroRect rect = m_parent->globalGeometry();

    return HiroRect(rect.x() + m_rect.x(), rect.y() + m_rect.y(),
                m_rect.width(), m_rect.height());

  }
}

void Widget::resize(int w, int h) {
  m_rect.setWidth(w);
  m_rect.setHeight(h);

  updateValid();
}

void Widget::move(int x, int y) {
  m_rect.setX(x);
  m_rect.setY(y);

  updateValid();

  updateOffset();
}

void Widget::onValidChanged() {
}

void Widget::onOffsetChanged() {
}

void Widget::updateOffset() {
  if (m_parent == NULL)
    setOffset(m_rect.x(), m_rect.y());
  else {
    const HiroPoint p = m_parent->offset();

    setOffset(p.x() + m_rect.x(), p.y() + m_rect.y());
  }

  onOffsetChanged();

  if (m_children != NULL) {
    for (unsigned int i = 0; i < m_children->size(); ++i)
      m_children->at(i)->updateOffset();
  }

}

void Widget::updateValid() {
  HiroRect pRect;

  if (m_parent == NULL) {
    pRect = HiroRect(0, 0, Painter::sWidth, Painter::sHeight);
  } else {
    const HiroRect rect = m_parent->validRect();

    pRect = rect;
  }

  if (m_rect.x() < pRect.x()) {
    if (m_rect.x() + m_rect.width() < pRect.x()) {
      m_valid_rect.setX(0);
      m_valid_rect.setWidth(0);
    } else {
      m_valid_rect.setX(pRect.x() - m_rect.x());
      int w = m_rect.width() - m_valid_rect.x();

      if (w > pRect.width())
        m_valid_rect.setWidth(pRect.width());
      else
        m_valid_rect.setWidth(w);
    }
  } else {
    m_valid_rect.setX(0);

    int w = pRect.width() - (m_rect.x() - pRect.x());

    if (w > m_rect.width())
      m_valid_rect.setWidth(m_rect.width());
    else
      m_valid_rect.setWidth(w);
  }

  if (m_rect.y() < pRect.y()) {
    if (m_rect.y() + m_rect.height() < pRect.y()) {
      m_valid_rect.setY(0);
      m_valid_rect.setHeight(0);
    } else {
      m_valid_rect.setY(pRect.y() - m_rect.y());
      int h = m_rect.height() - m_rect.y();

      if (h > pRect.height())
        m_valid_rect.setHeight(pRect.height());
      else
        m_valid_rect.setHeight(h);
    }
  } else {
    m_valid_rect.setY(0);

    int h = pRect.height() - (m_rect.y() - pRect.y());

    if (h > m_rect.height())
      m_valid_rect.setHeight(m_rect.height());
    else
      m_valid_rect.setHeight(h);
  }

  onValidChanged();
  //cout << m_valid_rect.toString() << endl;

  if (m_children != NULL) {
    for (unsigned int i = 0; i < m_children->size(); ++i)
      m_children->at(i)->updateValid();
  }

}

void Widget::updateValidRect(const HiroRect &rect, HiroRect &validRect) {
  HiroRect pRect = validRect();

  if (rect.x() < pRect.x()) {
    if (rect.x() + rect.width() < pRect.x()) {
      validRect.setX(0);
      validRect.setWidth(0);
    } else {
      validRect.setX(pRect.x() - rect.x());
      int w = rect.width() - validRect.x();

      if (w > pRect.width())
        validRect.setWidth(pRect.width());
      else
        validRect.setWidth(w);
    }
  } else {
    validRect.setX(0);

    int w = pRect.width() - (rect.x() - pRect.x());

    if (w > rect.width())
      validRect.setWidth(rect.width());
    else
      validRect.setWidth(w);
  }

  if (rect.y() < pRect.y()) {
    if (rect.y() + rect.height() < pRect.y()) {
      validRect.setY(0);
      validRect.setHeight(0);
    } else {
      validRect.setY(pRect.y() - rect.y());
      int h = rect.height() - rect.y();

      if (h > pRect.height())
        validRect.setHeight(pRect.height());
      else
        validRect.setHeight(h);
    }
  } else {
    validRect.setY(0);

    int h = pRect.height() - (rect.y() - pRect.y());

    if (h > rect.height())
      validRect.setHeight(rect.height());
    else
      validRect.setHeight(h);
  }
}

void Widget::setParent(Widget *parent) {
  if (m_parent != NULL)
    m_parent->removeChild(this);

  m_parent = parent;

  if (m_parent == NULL)
    mIndexInParent = -1;
  else
    m_parent->addChild(this);

  updateValid();

  updateOffset();
}

Widget *Widget::getParent() {
  return m_parent;
}

bool Widget::addChild(Widget *child) {
  if (child == NULL)
    return false;

  if (m_children == NULL)
    m_children = new vector<Widget *>;

  child->setIndexInParent(m_children->size());

  m_children->push_back(child);

  return true;

}

bool Widget::addChildToPositon(Widget *child, unsigned int pos) {
  if (child == NULL)
    return false;

  if (m_children == NULL)
    m_children = new vector<Widget *>;

  if (pos >= m_children->size()) {
    child->setIndexInParent(m_children->size());

    m_children->push_back(child);
  } else {
    m_children->insert(m_children->begin() + pos, child);
    for (unsigned int i = 0; i < m_children->size(); ++i) {
      m_children->at(i)->setIndexInParent(i);
    }
  }

  return true;

}

bool Widget::removeChild(Widget *child) {
  if (child == NULL
    || m_children == NULL)
    return false;

  int index = child->getIndexInParent();
  if (index < 0
    || (unsigned int) index >= m_children->size())
    return false;
  else {
    if (m_children->at(index) == child) {
      m_children->erase(m_children->begin() + index);
      for (unsigned int i = 0; i < m_children->size(); ++i) {
        m_children->at(i)->setIndexInParent(i);
      }
    } else
    return false;
  }

  return true;
}

void Widget::fall() {
  m_parent->removeChild(this);
  m_parent->addChildToPositon(this, 0);
}

void Widget::rise() {
}

void Widget::reverseChild() {
  if (m_children != NULL) {
    unsigned int size = m_children->size();
    if (size > 0) {
      reverse(m_children->begin(), m_children->end());

      for (unsigned int i = 0; i < size; ++i) {
        //cout << m_children->at(i)->getIndexInParent() << endl;
        m_children->at(i)->setIndexInParent(i);
        //cout << m_children->at(i)->getIndexInParent() << endl;
      }
    }
  }
}

void Widget::removeAllChild() {
  if (m_children != NULL) {
    for (unsigned int i = 0; i < m_children->size(); ++i) {
      m_children->at(i)->setParent(NULL);
    }

    m_children->clear();
  }

}

void Widget::onShow() {
}

void Widget::onHide() {
}

void Widget::hide() {
  if (m_visible) {
    m_visible = false;
    m_is_hided = false;
    onHide();

    update();
  }
}

void Widget::show() {
  if (!m_visible) {
    m_is_hided = false;
    m_visible = true;
    onShow();
    update();
  }
}

void Widget::update() {
  if (!m_visible) {
    if (m_is_hided)
      return;
    else
      m_is_hided = true;
  }

  if (m_parent == NULL)

    m_dirty = true;
  else
    m_parent->update();
}

bool Widget::isParentDirty() {
  if (m_parent != NULL)
    return m_parent->isParentDirty();
  else
    return m_dirty;
}

void Widget::onDraw() {
}

void Widget::draw() {
  if (isParentDirty()) {
    if (m_visible) {
      onDraw();
      if (m_children != NULL) {
        for (unsigned int i = 0; i < m_children->size(); ++i)
          m_children->at(i)->draw();
      }

      m_dirty = false;
    }
  }

}


//------------------Focus----------------

bool Widget::isFocusIn() {
  return hasFocus;
}

void Widget::onFocusIn(HiroRect r) {};

void Widget::onFocusOut() {};

void Widget::focusIn(HiroRect r) {
  hasFocus = true;

  if (m_parent != NULL)
    m_parent->setChildFocus(this);

  onFocusIn(r);
}

void Widget::focusOut() {
  hasFocus = false;

  if (m_children != NULL) {
    for (unsigned int i = 0; i < m_children->size(); ++i)
      m_children->at(i)->setFocus(false);
  }

  mFocusChild = NULL;

  onFocusOut();
}

bool Widget::setFocus(bool focus) {
  if (focus == hasFocus)
    return false;

  if (focus) {
    HiroRect rect(0, 0, 0, 0);
    focusIn(rect);
  } else
  focusOut();

  return true;
}

void Widget::setChildFocus(Widget *child) {
  if (m_children != NULL) {
    for (unsigned int i = 0; i < m_children->size(); ++i) {
      if (m_children->at(i) != child)
        m_children->at(i)->setFocus(false);
    }
  }

  mFocusChild = child;
}

void Widget::setLeftFocus(Widget *widget) {
  mLeftFocus = widget;
}

void Widget::setRightFocus(Widget *widget) {
  mRightFocus = widget;
}

void Widget::setUpFocus(Widget *widget) {
  //cout << "Widget :: setUpFocus" << endl;
  mUpFocus = widget;
}
void Widget::clearUpFocus() {
  mUpFocus = NULL;
}

void Widget::setDownFocus(Widget *widget) {
  mDownFocus = widget;
}

bool Widget::focusLeft() {
  bool ret = true;

  if (mFocusChild != NULL) {
    if (!mFocusChild->focusLeft()) {
      if (mLeftFocus != NULL) {
        HiroRect rect = mFocusChild->globalGeometry();
        mFocusChild = NULL;
        mLeftFocus->focusIn(rect);
      } else
      ret = false;
    }
  } else {
    if (mLeftFocus != NULL) {
      mFocusChild = NULL;
      mLeftFocus->focusIn(globalGeometry());
    } else
    ret = false;
  }

  return ret;
}

bool Widget::focusRight() {
  bool ret = true;

  if (mFocusChild != NULL) {
    if (!mFocusChild->focusRight()) {
      if (mRightFocus != NULL) {
        HiroRect rect = mFocusChild->globalGeometry();
        mFocusChild = NULL;
        mRightFocus->focusIn(rect);
      } else
      ret = false;
    }
  } else {
    if (mRightFocus != NULL) {
      mFocusChild = NULL;
      mRightFocus->focusIn(globalGeometry());
    } else
    ret = false;
  }

  return ret;
}

bool Widget::focusUp() {
bool ret = true;
if (mFocusChild != NULL) {
#if 0
if(mFocusChild->mIsGameList == 1)
{
  if(!mFocusChild->focusUp())
  {
    if(mFocusChild->mUpFocus != NULL)
    {
      HiroRect rect = mFocusChild->mFocusChild->globalGeometry();
      mFocusChild->mFocusChild = NULL;

      mFocusChild->mUpFocus->focusIn(rect);
    }else
    ret = false;
  }
}
else if(mFocusChild->mIsGameList == 0)
{
  #endif
  //			cout << "up  1111" << endl;
  if (!mFocusChild->focusUp()) {
    if (mUpFocus != NULL) {
      HiroRect rect = mFocusChild->globalGeometry();
      mFocusChild = NULL;
      mUpFocus->focusIn(rect);
    } else
    ret = false;
  }
  //	}
} else {
  if (mUpFocus != NULL) {
    mFocusChild = NULL;
    mUpFocus->focusIn(globalGeometry());
  } else
  ret = false;
}

return ret;
}

bool Widget::focusDown() {
  bool ret = true;

  if (mFocusChild != NULL) {
    if (!mFocusChild->focusDown()) {
      if (mDownFocus != NULL) {
        HiroRect rect = mFocusChild->globalGeometry();
        mFocusChild = NULL;
        mDownFocus->focusIn(rect);
      } else
      ret = false;
    }
  } else {
    if (mDownFocus != NULL) {
      mFocusChild = NULL;
      mDownFocus->focusIn(globalGeometry());
    } else
    ret = false;
  }

  return ret;
}

bool Widget::onClick() {
  return false;
}

bool Widget::click() {
  if (mFocusChild != NULL) {
    if (!mFocusChild->click())
      return onClick();
    else
      return true;
  } else
  return onClick();
}

bool Widget::onBack() {
  return false;
}

bool Widget::back() {
  if (mFocusChild != NULL) {
    if (!mFocusChild->back())
      return onBack();
    else
      return true;
  } else
  return onBack();
}

//----------------- Anim -------------------------
void Widget::pauseAnimCallback() {
  pauseAnim();

  if (m_children != NULL) {
    for (unsigned int i = 0; i < m_children->size(); ++i)
      m_children->at(i)->pauseAnimCallback();
  }
}

void Widget::resumeAnimCallback() {
  resumeAnim();

  if (m_children != NULL) {
    for (unsigned int i = 0; i < m_children->size(); ++i)
      m_children->at(i)->resumeAnimCallback();
  }
}

void Widget::onConfigurationChanged(int changed) {
}

void Widget::configurationChanged(int changed) {
  onConfigurationChanged(changed);

  if (m_children != NULL) {
    for (unsigned int i = 0; i < m_children->size(); ++i)
      m_children->at(i)->configurationChanged(changed);
  }
}

//-------------------- attach ------------
void Widget::onAttach() {
}

void Widget::onDettach() {
}

int Widget::getImageW() {

}
void Widget::ScalImage(int w) {

}

void Widget::attach() {
  onAttach();

  if (m_children != NULL) {
    for (unsigned int i = 0; i < m_children->size(); ++i)
      m_children->at(i)->attach();
  }
}

void Widget::dettach() {
  onDettach();

  if (m_children != NULL) {
    for (unsigned int i = 0; i < m_children->size(); ++i)
      m_children->at(i)->dettach();
  }
}
#endif
