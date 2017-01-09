#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"


using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    //setTouchMode(kCCTouchesOneByOne);
    setTouchEnabled(true);
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    spriteTexture = CCSpriteBatchNode::create("HelloWorld.png");

    // position the sprite on the center of the screen
    spriteTexture->setPosition( ccp(size.width/2, size.height/2)  );

    // add the sprite as a child to this layer
    this->addChild(spriteTexture, 1);
    //spriteTexture->setOpacity(0);
    
    pSprite = CCSprite::create("HelloWorld.png");
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    this->addChild(pSprite, 1);
    pSprite->setOpacity(0);
    
    CCSprite *bg = CCSprite::create("bg_1.jpg");
    
    bg->setPosition( ccp(size.width/2, size.height/2) );
    

    
    // add the sprite as a child to this layer
    this->addChild(bg, 0);
    
    this->getImage();
    
    return true;
}

void HelloWorld::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    
}

void HelloWorld::ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    CCSize s = pSprite->getContentSize();
    CCPoint p = pSprite->getPosition();
    CCPoint ap = pSprite->getAnchorPoint();
    
    CCRect rect = CCRectMake( p.x - ap.x * s.width ,p.y - ap.y * s.height,s.width, s.height);
    
    CCTouch * touch = (CCTouch *)(* touches->begin());
    CCPoint point =  touch->getLocationInView();
    point = CCDirector::sharedDirector()->convertToGL(point);
    
    
    if(rect.containsPoint(point))
    {
        //pSprite->setOpacity(255);
        
        //如果只显示一小部分
        
        //CCRect subRect = CCRectMake(point.x - 10 - 240, point.y -10 -160, 20, 20);
        CCRect subRect = CCRectMake(point.x - 240, point.y -160, 20, 20);
        //CCSprite* sprite = CCSprite::createWithTexture(spriteTexture->getTexture());
        CCSprite* sprite = CCSprite::createWithTexture(spriteTexture->getTexture(), subRect);
        sprite->setPosition(point);
        this->addChild(sprite, 2);
        
        //pSprite->cocos2d::CCTextureProtocol::getTexture()
        //        pSprite->setTextureRect(subRect);
        //        pSprite->setOpacity(255);
        //pSprite->getTexture()->ge
        
    }else
    {
        //pSprite->setOpacity(0);
    }
}
void HelloWorld::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{

    
}
void HelloWorld::ccTouchCancelled(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    ccTouchesEnded(touches, event);
}




void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::getImage()
{
    //
    const char* names[64] = { "other" };
	for (int i = 0; i < 1; i++)
	{
        std::string plist = std::string("temp/") + names[i] + ".plist";
		const char* pListfile = plist.c_str();
		std::string png = std::string("temp/") + names[i] + ".png";
		const char* pathKey = png.c_str();
        
        //CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pListfile, pathKey);
        CCTextureCache::sharedTextureCache()->addPVRImage(pathKey);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pListfile);
        
        CCDictionary *dict = CCDictionary::createWithContentsOfFileThreadSafe(pListfile);
        CCDictionary *framesDict = (CCDictionary*)dict->objectForKey("frames");
        CCDictElement* pElement = NULL;
        
        std::string pathString = CCFileUtils::sharedFileUtils()->getWritablePath();
        
        CCLog("pathString : %s", pathString.c_str());
        
        CCDICT_FOREACH(framesDict, pElement)
        {
            //CCDictionary* frameDict = (CCDictionary*)pElement->getObject();
            std::string spriteFrameName = pElement->getStrKey();
            //CCLOG("framename:%s",spriteFrameName.c_str());
            
            CCSprite* pNode = CCSprite::createWithSpriteFrameName(spriteFrameName.c_str());
            
            //std::string fileString = pathString + spriteFrameName;
            
            this->saveNodeShot(pNode, spriteFrameName.c_str());
        }
    }
}

void HelloWorld::saveNodeShot(CCNode* pNode,const char*filename)
{
    CCPoint formerPos = pNode->getPosition();
	CCSize size = pNode->getContentSize();
	pNode->setPosition(ccp(size.width/2,size.height/2));
	CCRenderTexture* screen = CCRenderTexture::create(size.width, size.height);
	//screen->clear(1,1,1,1);
	screen->begin();
	pNode->visit();
	screen->end();
	//screen->saveToFile(filename, kCCImageFormatPNG);
    screen->saveToFile(filename, kCCImageFormatPNG);
	CC_SAFE_DELETE(screen);
	pNode->setPosition(formerPos);
}
