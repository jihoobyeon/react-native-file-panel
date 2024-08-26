#import "FilePanel.h"

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import <UniformTypeIdentifiers/UTType.h>

@implementation FilePanel
RCT_EXPORT_MODULE()

// Don't compile this code when we build for the old architecture.
#ifdef RCT_NEW_ARCH_ENABLED
- (NSData *)openFile:(NSArray<NSString *>)ext resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject {
		NSOpenPanel *panel = [NSOpenPanel openPanel];
		NSData *file = nil;
		
		[panel setCanChooseFiles:YES];
		[panel setCanChooseDirectories:NO];
		[panel setCanCreateDirectories:YES];
		[panel allowsMultipleSelection:NO];
		if (ext.count <= 0 || [ext[0] isEqualToString:@"*"]) {
				[panel setAllowsOtherFileTypes:YES];
		}
		else {
				NSMutableArray<UTType *> types = [NSMutableArray arrayWithCapacity:ext.count];
				for (NSString *extension in ext) {
						UTType *type = [UTType typeWithFilenameExtension:[extension substringFromIndex:1]];
						if (type != nil) {
								[types addObject:type];
						}
				}
				[panel setAllowedContentTypes:[types copy]];
				[panel setAllowsOtherFileTypes:NO];
		}
		
		if ([panel runModal] == NSModalResponseOK) {
				file = [NSData dataWithContentsOfURL:[panel URL]];
		}
		[panel close];
		
		if (file) {
				resolve(file);
		}
		else {
				reject(@"No file selected", @"No file selected", nil);
		}
}

- (NSArray<NSData *>)openFiles:(NSArray<NSString *>)ext resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject {
		NSOpenPanel *panel = [NSOpenPanel openPanel];
		NSArray<NSData *>files = @[];
		
		[panel setCanChooseFiles:YES];
		[panel setCanChooseDirectories:NO];
		[panel setCanCreateDirectories:YES];
		[panel allowsMultipleSelection:YES];
		if (ext.count <= 0 || [ext[0] isEqualToString:@"*"]) {
				[panel setAllowsOtherFileTypes:YES];
		}
		else {
				NSMutableArray<UTType *> types = [NSMutableArray arrayWithCapacity:ext.count];
				for (NSString *extension in ext) {
						UTType *type = [UTType typeWithFilenameExtension:[extension substringFromIndex:1]];
						if (type != nil) {
								[types addObject:type];
						}
				}
				[panel setAllowedContentTypes:[types copy]];
				[panel setAllowsOtherFileTypes:NO];
		}
		
		if ([panel runModal] == NSModalResponseOK) {
				NSMutableArray<NSData *> temp = [NSMutableArray arrayWithCapacity:[[panel URLs] count]];
				for (NSURL *file in [panel URLs]) {
						[temp addObject:[NSData dataWithContentsOfURL:file]];
				}
				files = temp;
		}
		[panel close];
		
		if (files.count > 0) {
				resolve(files);
		}
		else {
				reject(@"No file selected", @"No file selected", nil);
		}
}

- (NSData *)openFolder resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject {
		NSOpenPanel *panel = [NSOpenPanel openPanel];
		NSURL *folder = nil;
		
		[panel setCanChooseFiles:NO];
		[panel setCanChooseDirectories:YES];
		[panel setCanCreateDirectories:YES];
		[panel allowsMultipleSelection:NO];
		[panel setAllowsOtherFileTypes:NO];
		
		if ([panel runModal] == NSModalResponseOK) {
				folder = [panel URL];
		}
		[panel close];
		
		if (file) {
				resolve(folder);
		}
		else {
				reject(@"No file selected", @"No file selected", nil);
		}
}

- (void)saveFile:(NSData *)content (NSArray<NSString *>)ext resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject {
		NSSavePanel *panel = [NSSavePanel savePanel];
		
		[panel setCanChooseFiles:YES];
		[panel setCanChooseDirectories:NO];
		[panel setCanCreateDirectories:YES];
		[panel allowsMultipleSelection:NO];
		if (ext.count <= 0 || [ext[0] isEqualToString:@"*"]) {
				[panel setAllowsOtherFileTypes:YES];
		}
		else {
				NSMutableArray<UTType *> types = [NSMutableArray arrayWithCapacity:ext.count];
				for (NSString *extension in ext) {
						UTType *type = [UTType typeWithFilenameExtension:[extension substringFromIndex:1]];
						if (type != nil) {
								[types addObject:type];
						}
				}
				[panel setAllowedContentTypes:[types copy]];
				[panel setAllowsOtherFileTypes:NO];
		}
		
		if ([panel runModal] == NSModalResponseOK) {
				NSURL *file = [panel URL];
				[content writeToFile:[selectedFile path] atomically:NO encoding:NSUTF8StringEncoding error:nil];
		}
		[panel close];
  
		if(file) {
				resolve(nil);
		}
		else {
				reject(@"No file selected", @"No file selected", nil);
		}
}

- (std::shared_ptr<facebook::react::TurboModule>)getTurboModule:
    (const facebook::react::ObjCTurboModule::InitParams &)params
{
    return std::make_shared<facebook::react::NativeFilePanelSpecJSI>(params);
}
#endif

@end
