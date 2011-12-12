//
//  SMAppDelegate.h
//  dispatch-cancel
//
//  Created by Jerry Jones on 12/11/11.
//  Copyright (c) 2011 Spaceman Labs. All rights reserved.
//

#import <UIKit/UIKit.h>

@class SMViewController;

@interface SMAppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (strong, nonatomic) SMViewController *viewController;

@end
