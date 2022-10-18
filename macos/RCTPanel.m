//
//  RCTPanel.m
//  macOSPanel
//
//  Created by Jihoo Byeon on 2022/09/26.
//

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import <UniformTypeIdentifiers/UTType.h>
#import "RCTPanel.h"
@implementation RCTPanel

RCT_EXPORT_MODULE();

RCT_EXPORT_METHOD(open:(NSString *)ext
  resolver:(RCTPromiseResolveBlock)resolve
  rejecter:(RCTPromiseRejectBlock)reject)
{
  NSOpenPanel *panel = [NSOpenPanel openPanel];
  NSObject *file;
  UTType *type = [UTType typeWithFilenameExtension:[ext substringFromIndex:1]];
  [panel setAllowedContentTypes:@[type]];
  [panel setAllowsOtherFileTypes:NO];
  [panel setCanChooseFiles:YES];
  [panel setCanChooseDirectories:NO];
  [panel setCanCreateDirectories:NO];
  if ([panel runModal] == NSModalResponseOK)
  {
    for(NSURL *selectedFile in [panel URLs])
    {
      file = [selectedFile path];
    }
  }
  [panel close];
  if(file) {
		resolve(file);
	} else {
		reject(@"No file selected", @"No file selected", nil);
	}
}

RCT_EXPORT_METHOD(save:(NSString *)ext
  content:(NSString *)content
  resolver:(RCTPromiseResolveBlock)resolve
  rejecter:(RCTPromiseRejectBlock)reject)
{
  NSSavePanel *panel = [NSSavePanel savePanel];
  NSObject *file;
  UTType *type = [UTType typeWithFilenameExtension:[ext substringFromIndex:1]];
  [panel setAllowedContentTypes:@[type]];
  [panel setAllowsOtherFileTypes:NO];
  [panel setCanCreateDirectories:YES];
  if ([panel runModal] == NSModalResponseOK)
  {
    NSURL *selectedFile = [panel URL];
    [content writeToFile:[selectedFile path]
    atomically:NO
    encoding:NSUTF8StringEncoding
    error:nil];
    file = [selectedFile path];
  }
  [panel close];
  if(file) {
		resolve(file);
	} else {
		reject(@"No file selected", @"No file selected", nil);
	}
}

- (dispatch_queue_t)methodQueue
{
  return dispatch_get_main_queue();
}

@end

