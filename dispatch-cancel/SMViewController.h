//
//  SMViewController.h
//  dispatch-cancel
//
//  Created by Jerry Jones on 12/11/11.
//  Copyright (c) 2011 Spaceman Labs. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SpacemanBlocks.h"

@interface SMViewController : UIViewController
{
	__block SMDelayedBlockHandle _delayedBlockHandle;
	BOOL _waiting;
}

@property (nonatomic, retain) IBOutlet UILabel *statusLabel;
@property (nonatomic, retain) IBOutlet UIButton *button;

- (IBAction)buttonPress:(id)sender;

@end
