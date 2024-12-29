#import <Cocoa/Cocoa.h>

@interface PopupWindowController : NSWindowController
@end

@implementation PopupWindowController

- (instancetype)init {
    self = [super initWithWindow:nil];
    if (self) {
        NSWindow *popupWindow = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 300, 200)
                                                            styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable)
                                                              backing:NSBackingStoreBuffered
                                                                defer:NO];
        popupWindow.title = @"Popup Window";
        [popupWindow center];
        self.window = popupWindow;

        // Add a label to the popup window
        NSTextField *label = [[NSTextField alloc] initWithFrame:NSMakeRect(50, 80, 200, 40)];
        label.stringValue = @"This is a popup!";
        label.bezeled = NO;
        label.drawsBackground = NO;
        label.editable = NO;
        label.alignment = NSTextAlignmentCenter;
        [popupWindow.contentView addSubview:label];
    }
    return self;
}

@end

@interface AppDelegate : NSObject <NSApplicationDelegate>
@property (strong) NSWindow *mainWindow;
@property (strong) PopupWindowController *popupController;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
    // Create the main application window
    self.mainWindow = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 400, 300)
                                                  styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskResizable | NSWindowStyleMaskClosable)
                                                    backing:NSBackingStoreBuffered
                                                      defer:NO];
    self.mainWindow.title = @"Main Window";
    [self.mainWindow center];
    [self.mainWindow makeKeyAndOrderFront:nil];

    // Add a button to open the popup
    NSButton *popupButton = [[NSButton alloc] initWithFrame:NSMakeRect(150, 130, 100, 30)];
    popupButton.title = @"Show Popup";
    popupButton.bezelStyle = NSBezelStyleRounded;
    popupButton.target = self;
    popupButton.action = @selector(showPopup);
    [self.mainWindow.contentView addSubview:popupButton];
}

- (void)showPopup {
    if (!self.popupController) {
        self.popupController = [[PopupWindowController alloc] init];
    }
    [self.popupController showWindow:nil];
}

@end

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSApplication *app = [NSApplication sharedApplication];
        AppDelegate *delegate = [[AppDelegate alloc] init];
        app.delegate = delegate;
        return NSApplicationMain(argc, argv);
    }
}
