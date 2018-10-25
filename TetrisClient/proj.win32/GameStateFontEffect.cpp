#include "GameStateFontEffect.h"



CGameStateFontEffect::CGameStateFontEffect()
{
}


CGameStateFontEffect::~CGameStateFontEffect()
{
}

void CGameStateFontEffect::Clear()
{
	removeAllChildren();
}


void CGameStateFontEffect::SetState(int state)
{
	removeAllChildren();
	m_callBack = nullptr;

	m_nState = state;
}

void CGameStateFontEffect::PlayEffect()
{
	m_callBack = nullptr;


	switch (m_nState)
	{
	case kPrepareHost:
	{
		auto textField = Label::createWithBMFont("fonts/west_england-64.fnt", "Ready");
		textField->setTag(0);
		addChild(textField);

		auto moveAction = MoveBy::create(0.5, Vec2::Vec2(0, -60));
		auto easeExpAction = EaseExponentialInOut::create(moveAction);

		auto squenceAction = Sequence::create(easeExpAction, CallFunc::create([textField]() {
			textField->setString("3");
			textField->setPosition(Vec2::ZERO);
		}),
			easeExpAction, CallFunc::create([textField]() {
			textField->setString("2");
			textField->setPosition(Vec2::ZERO);

		}),
			easeExpAction, CallFunc::create([textField]() {
			textField->setString("1");
			textField->setPosition(Vec2::ZERO);

		}), 
			easeExpAction,
			nullptr
			);


		textField->runAction(squenceAction);

		break;
	}

	case kPrepare:
	{
		auto textField = Label::createWithBMFont("fonts/west_england-64.fnt", "Ready");
		textField->setTag(0);
		addChild(textField);
		break;
	}

	case kPause:
	{
		auto textField = Label::createWithBMFont("fonts/west_england-64.fnt", "Ready");
		textField->setTag(0);
		addChild(textField);
		break;
	}


	case kReady:
	{
		auto textField = Label::createWithBMFont("fonts/west_england-64.fnt", "Ready");
		textField->setTag(0);
		addChild(textField);
		break;
	}


	case kPlay:
	{
		auto textField = Label::createWithBMFont("fonts/west_england-64.fnt", "Ready");
		textField->setTag(0);
		addChild(textField);
		break;
	}

	case kDead:
	{
		auto textField = Label::createWithBMFont("fonts/west_england-64.fnt", "Ready");
		textField->setTag(0);
		addChild(textField);
		break;
	}

	case kWait:
	{
		auto textField = Label::createWithBMFont("fonts/west_england-64.fnt", "Ready");
		textField->setTag(0);
		addChild(textField);
		break;
	}


	case kResultWin:
	{
		auto textField = Label::createWithBMFont("fonts/west_england-64.fnt", "Ready");
		textField->setTag(0);
		addChild(textField);
		break;
	}

	case kResultLose:
	{
		auto textField = Label::createWithBMFont("fonts/west_england-64.fnt", "Ready");
		textField->setTag(0);
		addChild(textField);
		break;
	}

	case kResultNone:
	{
		auto textField = Label::createWithBMFont("fonts/west_england-64.fnt", "Ready");
		textField->setTag(0);
		addChild(textField);
		break;
	}


	default:
		break;
	}
}

void CGameStateFontEffect::PlayEffect(std::function<void(int)> func)
{
	m_callBack = func;




	switch (m_nState)
	{
	case kPrepareHost:
	{
		auto textField = Label::createWithBMFont("fonts/west_england-64.fnt", "Prepare");
		textField->setTag(0);
		addChild(textField);


		auto nState = m_nState;
		auto moveAction = MoveBy::create(0.5, Vec2::Vec2(0, -60));
		auto easeExpAction = EaseExponentialInOut::create(moveAction);

		auto squenceAction = Sequence::create(
			Place::create(Vec2(0, 60))
			,easeExpAction, CallFunc::create([textField]() {
			textField->setString("3");
			textField->setPosition(Vec2::ZERO);
		}),
			easeExpAction, CallFunc::create([textField]() {
			textField->setString("2");
			textField->setPosition(Vec2::ZERO);

		}),
			easeExpAction, CallFunc::create([textField]() {
			textField->setString("1");
			textField->setPosition(Vec2::ZERO);

		}),
			easeExpAction,
			CallFunc::create([func, nState]()->void {
			func(nState);
			}),
			nullptr
			);


		textField->runAction(squenceAction);

		break;
	}

	case kPrepare:
	{
		auto textField = Label::createWithBMFont("fonts/west_england-64.fnt", "Ready");
		textField->setTag(0);
		addChild(textField);




		auto nState = m_nState;
		auto moveAction = MoveBy::create(0.5, Vec2::Vec2(0, -60));
		auto easeExpAction = EaseExponentialInOut::create(moveAction);

		auto squenceAction = Sequence::create(Place::create(Vec2(0, 60)), 
			easeExpAction,
			DelayTime::create(3.f),
			CallFunc::create([func, nState]()->void {
			func(nState);
		}),
			nullptr
			);


		textField->runAction(squenceAction);


		break;
	}

	case kPause:
	{
		auto textField = Label::createWithBMFont("fonts/west_england-64.fnt", "Ready");
		textField->setTag(0);
		addChild(textField);
		break;
	}


	case kReady:
	{
		auto textField = Label::createWithBMFont("fonts/west_england-64.fnt", "Ready");
		textField->setTag(0);
		addChild(textField);
		break;
	}


	case kPlay:
	{
		auto textField = Label::createWithBMFont("fonts/west_england-64.fnt", "Ready");
		textField->setTag(0);
		addChild(textField);
		break;
	}

	case kDead:
	{
		auto textField = Label::createWithBMFont("fonts/west_england-64.fnt", "Ready");
		textField->setTag(0);
		addChild(textField);
		break;
	}

	case kWait:
	{
		auto textField = Label::createWithBMFont("fonts/west_england-64.fnt", "Ready");
		textField->setTag(0);
		addChild(textField);
		break;
	}


	case kResultWin:
	{
		auto textField = Label::createWithBMFont("fonts/west_england-64.fnt", "Ready");
		textField->setTag(0);
		addChild(textField);
		break;
	}

	case kResultLose:
	{
		auto textField = Label::createWithBMFont("fonts/west_england-64.fnt", "Ready");
		textField->setTag(0);
		addChild(textField);
		break;
	}

	case kResultNone:
	{
		auto textField = Label::createWithBMFont("fonts/west_england-64.fnt", "Ready");
		textField->setTag(0);
		addChild(textField);
		break;
	}


	default:
		break;
	}
}
