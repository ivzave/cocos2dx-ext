About
---------------

CCPointer is a smart pointer class for using with Cocos2d-x objects.

Features
---------------

Using CCPointer you can:

   * safely use Cocos2d-x objects with STL containers and algorithms
   * not to care about explicitly initializing your pointers with NULL
   * not to care about releasing your pointers in destructors of your classes
   * use even no autorelease but have your pointers correctly released

How to use
---------------

You can use CCPointer just as ordinary C++ pointers - it supports all the operations supported by ordinary pointers.

Instead of
   CCType* pObj;
you should write
   CCPointer<CCType> pObj;

You can create local pointers or class members this way. You can pass them to functions accepting CCPointer or ordinary pointer (by value or by reference). Wrapped object will be retained whenever you create or copy CCPointer pointing to it and released each time a CCPointer gets destroyed or reassigned with another pointer. So the wrapped object will be kept alive as long as exists at least one CCPointer pointing to it.

Note
---------------

CCPointer assumes an object passed to it needs to be retained. It's ok to init CCPointer with autorelease() objects directly.

```CCPointer<CCSprite> pSprite(CCSprite::create[...]); // OK```

Whenever you need to pass an object that doesn't need to be retained (e.g. created with "new" operator) you should release it manually after creating CCPointer OR use provided helper function:

```CCPointer<CCSprite> pSprite(new CCSprite());
pSprite->release(); // this way```
   
```CCPointer<CCSprite> pSprite(CCReleaseMake(new CCSprite())); // or this way```
   
Contact
---------------

[http://github.com/ivzave/cocos2dx-ext]
Feel free to contact me with any suggestions or bug reports.
