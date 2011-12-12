//
//  SMViewController.m
//  dispatch-cancel
//
//  Created by Jerry Jones on 12/11/11.
//  Copyright (c) 2011 Spaceman Labs. All rights reserved.
//

#import "SMViewController.h"

@implementation SMViewController

@synthesize statusLabel;
@synthesize button;

- (void)dealloc
{
	self.statusLabel = nil;
	self.button = nil;
	[super dealloc];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
	[self.button addTarget:self action:@selector(buttonPress:) forControlEvents:UIControlEventTouchUpInside];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
	self.statusLabel = nil;
	self.button = nil;
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
}

- (void)viewDidDisappear:(BOOL)animated
{
	[super viewDidDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
	return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

- (IBAction)buttonPress:(id)sender
{
	if (_waiting) {
		
		if (nil != _delayedBlockHandle) {
			_delayedBlockHandle(YES);
		}
		_delayedBlockHandle = nil;
		
		self.statusLabel.text = @"Canceled";
		[self.button setTitle:@"Go" forState:UIControlStateNormal];
		_waiting = NO;
		
	} else {		
		self.statusLabel.text = @"Waiting";
		[self.button setTitle:@"Cancel" forState:UIControlStateNormal];
		
		_delayedBlockHandle = perform_block_after_delay(2.0f, ^{
			self.statusLabel.text = @"Done";
			[self.button setTitle:@"Go" forState:UIControlStateNormal];
			_delayedBlockHandle = nil;
			_waiting = NO;
		});
		
		_waiting = YES;
	}
}

@end
