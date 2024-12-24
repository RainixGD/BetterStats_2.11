#include "./includes.h"

#define public_cast(value, member) [](auto* v) { \
	class FriendClass__; \
	using T = std::remove_pointer<decltype(v)>::type; \
	class FriendeeClass__: public T { \
	protected: \
		friend FriendClass__; \
	}; \
	class FriendClass__ { \
	public: \
		auto& get(FriendeeClass__* v) { return v->member; } \
	} c; \
	return c.get(reinterpret_cast<FriendeeClass__*>(v)); \
}(value)
bool operator==(const cocos2d::CCPoint& a, const cocos2d::CCPoint& b) { return a.x == b.x && a.y == b.y; }
bool operator==(const cocos2d::CCRect& a, const cocos2d::CCRect& b) { return a.origin == b.origin && a.size == b.size; }

class BetterStatsManager {

	static BetterStatsManager* instance;
	
	void init() {
		
	}

	std::string thousandSeparator(int n) {
		std::string ans = "";

		std::string num = std::to_string(n);

		int count = 0;

		for (int i = num.size() - 1;
			i >= 0; i--) {
			count++;
			ans.push_back(num[i]);

			if (count == 3) {
				ans.push_back('.');
				count = 0;
			}
		}

		reverse(ans.begin(), ans.end());

		if (ans.size() % 4 == 0)
			ans.erase(ans.begin());

		return ans;
	}

	std::string intToFormatString(int num) {
		bool addMinus = 0;
		int n;
		if (num < 0) {
			n = std::abs(num);
			addMinus = 1;
		}
		else {
			n = num;
		}

		if (n < 1000 || n > 100000000)
			return std::to_string(n);

		std::string str = thousandSeparator(n);
		str = str.substr(0, str.find(".") + 2);

		char sufix;

		if (n < 1000000) sufix = 'K';
		else if (n < 100000000) sufix = 'M';


		return (addMinus ? "-" : "") + str + sufix;
	}

	float scaleMultiplyer(int value) {
		float mult = 1.f;
		if (value >= 1000)
			mult = 1.05;
		if (value >= 10000)
			mult = 1.1;
		if (value >= 1000000)
			mult = 1.3;
		return mult;
	}

	BetterStatsManager() {};

	CCNode* getStatsNode(CCNode* accountLayer) {
		CCObject* obj;
		CCARRAY_FOREACH_REVERSE(accountLayer->getChildren(), obj) {
			auto NodeObj = reinterpret_cast<CCNode*>(obj);
			CCObject* child;
			CCARRAY_FOREACH(NodeObj->getChildren(), child) {
				if (auto sprite_node = dynamic_cast<CCSprite*>(child); sprite_node) {
					auto* texture = sprite_node->getTexture();
					CCDictElement* el;
					auto* frame_cache = CCSpriteFrameCache::sharedSpriteFrameCache();
					auto* cached_frames = public_cast(frame_cache, m_pSpriteFrames);
					const auto rect = sprite_node->getTextureRect();
					CCDICT_FOREACH(cached_frames, el) {
						auto* frame = static_cast<CCSpriteFrame*>(el->getObject());
						if (frame->getTexture() == texture && frame->getRect() == rect) {
							if (std::string(el->getStrKey()) == std::string("GJ_coinsIcon2_001.png"))
								return NodeObj;
						}
					}
				}
			}
		}
	}
public:
	
	void onProfilePage_loadPageFromUserInfo(ProfilePage* layer, GJUserScore* score) {
		auto accountLayer = reinterpret_cast<CCNode*>(layer->getChildren()->objectAtIndex(0));
		auto statsNode = getStatsNode(accountLayer);


		int maxLength = score->creatorPoints_ ? 52 : 60;

		int childrenCount = statsNode->getChildrenCount();
		for (int i = 0; i < childrenCount; i++) {
			if (auto label = dynamic_cast<CCLabelBMFont*>(statsNode->getChildren()->objectAtIndex(i))) {
				if (label->getString() == std::to_string(score->stars_)) {
					label->setString(intToFormatString(std::stoi(label->getString())).c_str());
					label->limitLabelWidth(maxLength, 0.6, 0.0);
				}
				if (label->getString() == std::to_string(score->diamonds_)) {
					label->setString(intToFormatString(std::stoi(label->getString())).c_str());
					label->limitLabelWidth(maxLength, 0.6, 0.0);
				}
				if (label->getString() == std::to_string(score->secretCoins_)) {
					label->setString(intToFormatString(std::stoi(label->getString())).c_str());
					label->limitLabelWidth(maxLength, 0.6, 0.0);
				}
				if (label->getString() == std::to_string(score->userCoins_)) {
					label->setString(intToFormatString(std::stoi(label->getString())).c_str());
					label->limitLabelWidth(maxLength, 0.6, 0.0);
				}
				if (label->getString() == std::to_string(score->demons_)) {
					label->setString(intToFormatString(std::stoi(label->getString())).c_str());
					label->limitLabelWidth(maxLength, 0.6, 0.0);
				}
				if (label->getString() == std::to_string(score->creatorPoints_)) {
					label->setString(intToFormatString(std::stoi(label->getString())).c_str());
					label->limitLabelWidth(maxLength, 0.6, 0.0);
				}
			}
		}
	}

	void onLevelCell_loadCustomLevelCell(LevelCell* cell) {
		int childrenCount = cell->m_pLayer->getChildrenCount();
		for (int i = 0; i < childrenCount; i++) {
			if (auto label = dynamic_cast<CCLabelBMFont*>(cell->m_pLayer->getChildren()->objectAtIndex(i))) {
				if (label->getString() == std::to_string(cell->m_pLevel->downloads)) {
					label->setString(intToFormatString(std::stoi(label->getString())).c_str());
					label->setScale(0.4);
				}
				if (label->getString() == std::to_string(cell->m_pLevel->likes)) {
					label->setString(intToFormatString(std::stoi(label->getString())).c_str());
					label->setScale(0.4);
				}
			}
		}
	}

	void onLevelInfoLayer_updateLabelValues(LevelInfoLayer* layer) {
		if (layer->m_pLabel2) {
			layer->m_pLabel2->setString(intToFormatString(std::stoi(layer->m_pLabel2->getString())).c_str());
			layer->m_pLabel2->setScale(0.5);
		}
		if (layer->m_pLabel3) {
			layer->m_pLabel3->setString(intToFormatString(std::stoi(layer->m_pLabel3->getString())).c_str());
			layer->m_pLabel3->setScale(0.5);
		}
	}

	void onCommentCell_updateLabelValues(CommentCell* cell) {
		if (cell->m_pLikeLabel)
			cell->m_pLikeLabel->setString(intToFormatString(std::stoi(cell->m_pLikeLabel->getString())).c_str());
	}

	void onGJScoreCell_loadFromScore(GJScoreCell* cell, GJUserScore* score) {
		int childrenCount = cell->m_pLayer->getChildrenCount();
		for (int i = 0; i < childrenCount; i++) {
			if (auto label = dynamic_cast<CCLabelBMFont*>(cell->m_pLayer->getChildren()->objectAtIndex(i))) {
				if (label->getString() == std::to_string(score->stars_)) {
					label->setString(intToFormatString(std::stoi(label->getString())).c_str());
					label->setScale(label->getScale() * scaleMultiplyer(score->stars_));
				}
				if (label->getString() == std::to_string(score->diamonds_)) {
					label->setString(intToFormatString(std::stoi(label->getString())).c_str());
					label->setScale(label->getScale() * scaleMultiplyer(score->diamonds_));
				}
				if (label->getString() == std::to_string(score->secretCoins_)) {
					label->setString(intToFormatString(std::stoi(label->getString())).c_str());
					label->setScale(label->getScale() * scaleMultiplyer(score->secretCoins_));
				}
				if (label->getString() == std::to_string(score->userCoins_)) {
					label->setString(intToFormatString(std::stoi(label->getString())).c_str());
					label->setScale(label->getScale() * scaleMultiplyer(score->userCoins_));
				}
				if (label->getString() == std::to_string(score->demons_)) {
					label->setString(intToFormatString(std::stoi(label->getString())).c_str());
					label->setScale(label->getScale() * scaleMultiplyer(score->demons_));
				}
				if (label->getString() == std::to_string(score->creatorPoints_)) {
					label->setString(intToFormatString(std::stoi(label->getString())).c_str());
					label->setScale(label->getScale() * scaleMultiplyer(score->creatorPoints_));
				}
			}
		}
	}

	static BetterStatsManager* getInstance() {
		if (!instance) {
			instance = new BetterStatsManager();
			instance->init();
		}
		return instance;
	}

};
BetterStatsManager* BetterStatsManager::instance = nullptr;

void(__thiscall* ProfilePage_loadPageFromUserInfo)(ProfilePage* self, GJUserScore* score);
void __fastcall ProfilePage_loadPageFromUserInfo_H(ProfilePage* self, void*, GJUserScore* score) {
	ProfilePage_loadPageFromUserInfo(self, score);
	BetterStatsManager::getInstance()->onProfilePage_loadPageFromUserInfo(self, score);
}

void(__thiscall* LevelCell_loadCustomLevelCell)(LevelCell* self);
void __fastcall LevelCell_loadCustomLevelCell_H(LevelCell* self) {
	LevelCell_loadCustomLevelCell(self);
	BetterStatsManager::getInstance()->onLevelCell_loadCustomLevelCell(self);
}

void(__thiscall* LevelInfoLayer_updateLabelValues)(LevelInfoLayer* self);
void __fastcall LevelInfoLayer_updateLabelValues_H(LevelInfoLayer* self) {
	LevelInfoLayer_updateLabelValues(self);
	BetterStatsManager::getInstance()->onLevelInfoLayer_updateLabelValues(self);
}

void(__thiscall* CommentCell_updateLabelValues)(CommentCell* self);
void __fastcall CommentCell_updateLabelValues_H(CommentCell* self) {
	CommentCell_updateLabelValues(self);
	BetterStatsManager::getInstance()->onCommentCell_updateLabelValues(self);
}

void(__thiscall* CommentCell_updateBGColor)(CommentCell* self, unsigned int index);
void __fastcall CommentCell_updateBGColor_H(CommentCell* self, void*, unsigned int index) {
	CommentCell_updateBGColor(self, index);
	BetterStatsManager::getInstance()->onCommentCell_updateLabelValues(self);
}

void(__thiscall* GJScoreCell_loadFromScore)(GJScoreCell* self, GJUserScore* score);
void __fastcall GJScoreCell_loadFromScore_H(GJScoreCell* self, void*, GJUserScore* score) {
	GJScoreCell_loadFromScore(self, score);
	BetterStatsManager::getInstance()->onGJScoreCell_loadFromScore(self, score);
}

void inject() {
#if _WIN32
	auto base = reinterpret_cast<uintptr_t>(GetModuleHandle(0));
	AllocConsole();
	freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
	MH_CreateHook(
		reinterpret_cast<void*>(base + 0x210040),
		reinterpret_cast<void*>(&ProfilePage_loadPageFromUserInfo_H),
		reinterpret_cast<void**>(&ProfilePage_loadPageFromUserInfo)
	);

	MH_CreateHook(
		reinterpret_cast<void*>(base + 0x5a020),
		reinterpret_cast<void*>(&LevelCell_loadCustomLevelCell_H),
		reinterpret_cast<void**>(&LevelCell_loadCustomLevelCell)
	);

	MH_CreateHook(
		reinterpret_cast<void*>(base + 0x17b170),
		reinterpret_cast<void*>(&LevelInfoLayer_updateLabelValues_H),
		reinterpret_cast<void**>(&LevelInfoLayer_updateLabelValues)
	);

	MH_CreateHook(
		reinterpret_cast<void*>(base + 0x610C0),
		reinterpret_cast<void*>(&CommentCell_updateLabelValues_H),
		reinterpret_cast<void**>(&CommentCell_updateLabelValues)
	);

	MH_CreateHook(
		reinterpret_cast<void*>(base + 0x60F00),
		reinterpret_cast<void*>(&CommentCell_updateBGColor_H),
		reinterpret_cast<void**>(&CommentCell_updateBGColor)
	);

	MH_CreateHook(
		reinterpret_cast<void*>(base + 0x61440),
		reinterpret_cast<void*>(&GJScoreCell_loadFromScore_H),
		reinterpret_cast<void**>(&GJScoreCell_loadFromScore)
	);

	MH_EnableHook(MH_ALL_HOOKS);
#endif
}

#if _WIN32
WIN32CAC_ENTRY(inject)
#endif