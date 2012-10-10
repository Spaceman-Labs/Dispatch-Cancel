//
//  SpacemanBlocks.h
//
//  Created by Jerry Jones on 12/11/11.
//  Copyright (c) 2011 Spaceman Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef void(^SMDelayedBlockHandle)(BOOL cancel);

static SMDelayedBlockHandle perform_block_after_delay(CGFloat seconds, dispatch_block_t block) {
	
	if (nil == block) {
		return nil;
	}
	
	// block is likely a literal defined on the stack, even though we are using __block to allow us to modify the variable 
	// we still need to move the block to the heap with a copy
	__block dispatch_block_t blockToExecute = [block copy];
	__block SMDelayedBlockHandle delayHandleCopy = nil;
	
	SMDelayedBlockHandle delayHandle = ^(BOOL cancel){		
		if (NO == cancel && nil != blockToExecute) {
			dispatch_async(dispatch_get_main_queue(), blockToExecute);
		}
		
		// Once the handle block is executed, canceled or not, we free blockToExecute and the handle.
		// Doing this here means that if the block is canceled, we aren't holding onto retained objects for any longer than necessary.
#if !__has_feature(objc_arc)
		[blockToExecute release];
		[delayHandleCopy release];
#endif
		
		blockToExecute = nil;
		delayHandleCopy = nil;
	};
		
	// delayHandle also needs to be moved to the heap.
	delayHandleCopy = [delayHandle copy];
	
	dispatch_after(dispatch_time(DISPATCH_TIME_NOW, seconds * NSEC_PER_SEC), dispatch_get_main_queue(), ^{
		if (nil != delayHandleCopy) {
			delayHandleCopy(NO);
		}
	});

	return delayHandleCopy;
};

static void cancel_delayed_block(SMDelayedBlockHandle delayedHandle) {
	if (nil == delayedHandle) {
		return;
	}
	
	delayedHandle(YES);
}