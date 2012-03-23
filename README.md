README
======

A convenience function for dispatching blocks after a delay, with the ability to cancel them.

A little more info about the impetus for this code can be found in a blog post here: [http://www.ultrajoke.net/2011/12/cancel-dispatch_after/](http://www.ultrajoke.net/2011/12/cancel-dispatch_after/)


SKIP TO THE GOOD STUFF
-------
The code is wrapped up in a project so it can be seen used in an example, but if you aren't interested in all the fluff, just grab the [SpacemanBlocks.h](https://github.com/Spaceman-Labs/Dispatch-Cancel/blob/master/dispatch-cancel/SpacemanBlocks.h) file


HOW IT WORKS
------------

Unlike using `dispatch_after`, `perform_block_after_delay` returns a handle that allows the execution of the block to be canceled at any time. Canceling a delayed block causes it to be released, allowing for the immediate freeing of memory potentially retained by objects within the delayed block.


HOW TO USE IT
-------------

`perform_block_after_delay` returns a SMDelayedBlockHandle block, typedef'd as follows:
	typedef void(^SMDelayedBlockHandle)(BOOL cancel);
	
If the returned handle is executed with it's argument set to `YES`, the execution of the delayed block is canceled, and the original block is released. If the returned handle is executed with it's argument set to `NO`, the delayed block is executed immediately and released - it will no longer be executed after the initially provided delay.

If a delayed block is expected to be canceled, it's handle should be retained for use at a later time. When this is the case, it is desirable to have the delayed block cleanup the out of date handle, there is a little bit of block juggling that needs to happen here.

	@interface SMViewController : UIViewController
	{
		__block SMDelayedBlockHandle _delayedBlockHandle;
	}
	@end
	
	@implementation SMViewController
	
	- (void)delayBlock
	{
		SMDelayedBlockHandle handle = perform_block_after_delay(2.0f, ^{
					// Work
					[_delayedBlockHandle release];
					_delayedBlockHandle = nil;
				});
		_delayedBlockHandle = [handle retain];
	}
	
	- (void)cancelBlock
	{
		if (nil == _delayedBlockHandle) {
			return;
		}
		
		_delayedBlockHandle(YES);
		[_delayedBlockHandle release];
		_delayedBlockHandle = nil;
	}
	
	@end


LICENSE
-------

Copyright (C) 2011 by Spaceman Labs

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.