#include "ChatLayer.h"
#include "NetworkThread.h"


CChatLayer::CChatLayer()
{
}


CChatLayer::~CChatLayer()
{
}


bool CChatLayer::init()
{

	auto pRedDot = Sprite::create("PosPoint.png");
	pRedDot->setPosition(500, 100);
	pRedDot->setScaleX(500.0 / 12.0);
	pRedDot->setScaleY(50.0 / 12.0);

	pRedDot->setAnchorPoint(Vec2::ZERO);
	this->addChild(pRedDot);


	pRedDot = Sprite::create("PosPoint.png");
	pRedDot->setPosition(100, 200);
	pRedDot->setScaleX(1000.0 / 12.0);
	pRedDot->setScaleY(600.0 / 12.0);
	pRedDot->setOpacity(0.5);
	pRedDot->setAnchorPoint(Vec2::ZERO);

	this->addChild(pRedDot);

	auto pTextField = TextFieldKR::textFieldWithPlaceHolder("<click here for input>",
		Size(500, 50),
		TextHAlignment::LEFT,
		"fonts/malgun.ttf",
		36);
	pTextField->setPosition(500, 100);
	pTextField->setAnchorPoint(Vec2::ZERO);
	pTextField->setTag(20);
	addChild(pTextField);
	
	for (int i = 0; i < 50; ++i)
	{
		std::string strTemp = StringUtils::format("%d", i);
		m_vecChatMsg.push_back(strTemp);
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(InputText::onTouchBegan, static_cast<InputText*>(this));
	listener->onTouchEnded = CC_CALLBACK_2(InputText::onTouchEnded, static_cast<InputText*>(this));
	//listener->onTouchBegan = CC_CALLBACK_2(InputText::onTouchBegan, this);
	//listener->onTouchEnded = CC_CALLBACK_2(InputText::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	AddTrackNode(pTextField);

	TableView* tableView = TableView::create(this, Size(1000, 600));
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	tableView->setPosition(Vec2(100, 200));
	tableView->setDelegate(this);
	tableView->setBounceable(false);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::BOTTOM_UP);
	this->addChild(tableView);
	tableView->reloadData();
	m_ptableView = tableView;

	bar = ScrollBar::creatScrollbar(tableView);

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ScrollBar::onTouchBegan, bar);
	listener->onTouchMoved = CC_CALLBACK_2(ScrollBar::onTouchMoved, bar);
	listener->onTouchEnded = CC_CALLBACK_2(ScrollBar::onTouchEnded, bar);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyReleased = CC_CALLBACK_2(CChatLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	AddTrackNode(pTextField);




	return Layer::init();
}


void CChatLayer::scrollViewDidScroll(ScrollView* view) {
	if (bar != nullptr && view != nullptr)
	{
		bar->OffsetRefresh(view->getContentOffset().y);
	}
}


void CChatLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
	CCLOG("cell touched at index: %ld", static_cast<long>(cell->getIdx()));
}

Size CChatLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return Size(100, 30);
}

TableViewCell* CChatLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
	//auto string = StringUtils::format("aaaa:aaaaaaaaaaaaaaaasdsda%ld", static_cast<long>(idx));
	string msg;
	if (idx < m_vecChatMsg.size())
	{
		msg = m_vecChatMsg.at(idx);
	}

	TableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new (std::nothrow) TableViewCell();
		cell->autorelease();
		cell->setContentSize(Size(100, 30));

		auto label = Label::createWithTTF(msg, "fonts/malgun.ttf", 32.0);
		label->setPosition(Vec2::ZERO);
		label->setAnchorPoint(Vec2::ZERO);
		label->setTag(123);
		cell->addChild(label);
	}
	else
	{
		auto label = (Label*)cell->getChildByTag(123);
		label->setString(msg);
	}


	return cell;
}

ssize_t CChatLayer::numberOfCellsInTableView(TableView *table)
{
	return m_vecChatMsg.size();
}

void CChatLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)
	{
		TextFieldKR* pTextField = static_cast<TextFieldKR*>(this->getChildByTag(20));

		if (m_vecChatMsg.size() >= m_nMaxChatMsg)
		{
			m_vecChatMsg.pop_front();
		}

		//m_vecChatMsg.push_back(pTextField->GetString());

		ServerMessage::Chat sendMessage;
		sendMessage.set_dst_id(10);
		sendMessage.set_name("aas");
		sendMessage.set_message(pTextField->GetString());

		CNetworkThread::GetMutable().SendPacket(ServerMessage::CHAT, &sendMessage);

		pTextField->Clear();
		/*
		m_ptableView->reloadData();

		bar->ContentRefresh(m_ptableView->getContentSize().height);
		bar->OffsetRefresh(m_ptableView->getContentOffset().y);
		//*/
	}
}


void CChatLayer::PushMessage(string message)
{
	if (m_vecChatMsg.size() >= m_nMaxChatMsg)
	{
		m_vecChatMsg.pop_front();
	}

	m_vecChatMsg.push_back(message);
	m_ptableView->reloadData();

	bar->ContentRefresh(m_ptableView->getContentSize().height);
	bar->OffsetRefresh(m_ptableView->getContentOffset().y);
}

void ChatScrollView::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	TableViewCell::draw(renderer, transform, flags);
}