#include "HelloWorldScene.h"
#include "MyBodyParser.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    
    scene->getPhysicsWorld()->setGravity( Vec2( 0, 0 ) );
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    layer->SetPhysicsWorld( scene->getPhysicsWorld() );

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
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto edgeBody = PhysicsBody::createEdgeBox( visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3 );
    
    auto edgeNode = Node::create();
    edgeNode->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    edgeNode->setPhysicsBody( edgeBody );
    
    this->addChild( edgeNode );
    
    auto sprite = Sprite::create( "Paddle.png" );
    sprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    MyBodyParser::getInstance()->parseJsonFile( "Paddle3.json" );
    
    auto spriteBody = MyBodyParser::getInstance()->bodyFormJson(sprite, "PaddleCool", PhysicsMaterial( 1, 1, 0 ) );
    
    if ( spriteBody != nullptr )
    {
        spriteBody->setDynamic( true );
        sprite->setPhysicsBody( spriteBody );
    }
    
    spriteBody->setVelocity(Vect(500, 40));
    
    this->addChild( sprite );
    
    return true;
}

