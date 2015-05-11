//
//  TasksViewController.m
//  todo
//
//  Created by Akshay Mhatre on 29/10/13.
//  Copyright (c) 2013 raweng. All rights reserved.
//

#import "TasksViewController.h"
#import "SVProgressHUD.h"
#import "AppDelegate.h"
@interface TasksViewController ()<UIAlertViewDelegate>

@end

@implementation TasksViewController

-(id)initWithStyle:(UITableViewStyle)style withBuiltClass:(BuiltClass *)builtClass{
    self = [super initWithStyle:style withBuiltClass:builtClass];
    if (self) {
        self.title = @"Tasks";
        self.enablePullToRefresh = YES;
        self.fetchLimit = 10;
        [self.builtQuery orderByDescending:@"created_at"];
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self refresh];
    
    //button to add a new task
    UIBarButtonItem *addButton = [[UIBarButtonItem alloc]initWithBarButtonSystemItem:UIBarButtonSystemItemAdd target:self action:@selector(addTasks)];
    [self.navigationItem setRightBarButtonItem:addButton];
}

#pragma mark Tasks
- (void)addTasks{
    UIAlertView *inputTask = [[UIAlertView alloc]initWithTitle:@"Task" message:nil delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Add", nil];
    [inputTask setAlertViewStyle:UIAlertViewStylePlainTextInput];
    [inputTask setDelegate:self];
    [inputTask show];
}

#pragma mark  UITableViewDataSource

-(void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath{
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        BuiltObject *task = [self.objectCollection objectAtIndex:indexPath.row];

        [tableView beginUpdates];
        [self.objectCollection removeObjectAtIndex:indexPath.row];
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationAutomatic];
        [tableView endUpdates];
        
        //delete a task
        [task destroyInBackgroundWithCompletion:^(ResponseType responseType, NSError *error) {
            if (error) {
                [self.objectCollection insertObject:task atIndex:indexPath.row];
                [tableView insertRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationAutomatic];
            }
        }];
    }
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath builtObject:(BuiltObject *)builtObject{
    static NSString *CellIdentifier = @"CellIdentifier";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier forIndexPath:indexPath];
    
    NSMutableAttributedString *attributeString;
    attributeString = [[NSMutableAttributedString alloc] initWithString:[builtObject objectForKey:@"task_name"]];
    
    if ([self isTaskDone:builtObject]) {
        attributeString = [self strikeTask:attributeString];
    }
    
    cell.textLabel.attributedText = attributeString;
    cell.textLabel.numberOfLines = 0;
    
    return cell;
}

-(BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath{
    return YES;
}

#pragma mark  UITableViewDelegate

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    [self strikeUnstrike:indexPath];
}

-(UITableViewCellEditingStyle)tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath{
    return UITableViewCellEditingStyleDelete;
}

-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath{
    BuiltObject *obj = [self builtObjectAtIndexPath:indexPath];
    CGSize size = [[obj objectForKey:@"task_name"] sizeWithFont:[UIFont systemFontOfSize:16] constrainedToSize:CGSizeMake(CGRectGetWidth(self.tableView.frame), 9999)];
    return size.height + 20;
}

#pragma mark  Task operations

- (NSMutableAttributedString *)strikeTask:(NSMutableAttributedString *)string{
    [string addAttribute:NSStrikethroughStyleAttributeName
                                   value:[NSNumber numberWithInt:1]
                                   range:(NSRange){0,[string length]}];
    return string;
}

- (NSMutableAttributedString *)unstrikeTask:(NSMutableAttributedString *)string{
    [string removeAttribute:NSStrikethroughStyleAttributeName
                   range:(NSRange){0,[string length]}];
    return string;
}



- (void)markAsDone:(NSIndexPath *)indexPath{
    UITableViewCell *cell = [self.tableView cellForRowAtIndexPath:indexPath];
    BuiltObject *obj = [self builtObjectAtIndexPath:indexPath];
    
    //update a task with task_status as YES
    [obj setObject:[NSNumber numberWithBool:YES] forKey:@"task_status"];
    [obj saveInBackgroundWithCompletion:^(ResponseType responseType, NSError *error) {
        if (error) {
            [self unstrikeTask:[cell.textLabel.attributedText mutableCopy]];
        }
    }];
}

- (void)markAsUnDone:(NSIndexPath *)indexPath{
    UITableViewCell *cell = [self.tableView cellForRowAtIndexPath:indexPath];
    BuiltObject *obj = [self builtObjectAtIndexPath:indexPath];
    
    //update a task with task_status as NO
    [obj setObject:[NSNumber numberWithBool:NO] forKey:@"task_status"];
    [obj saveInBackgroundWithCompletion:^(ResponseType responseType, NSError *error) {
        if (error) {
            [self isStriked:[cell.textLabel.attributedText mutableCopy]];
        }
    }];
}

- (void)strikeUnstrike:(NSIndexPath *)indexPath{
    UITableViewCell *cell = [self.tableView cellForRowAtIndexPath:indexPath];
    
    if ([self isStriked:[cell.textLabel.attributedText mutableCopy]]) {
        cell.textLabel.attributedText = [self unstrikeTask:[cell.textLabel.attributedText mutableCopy]];
        [self markAsUnDone:indexPath];
    }else{
        cell.textLabel.attributedText = [self strikeTask:[cell.textLabel.attributedText mutableCopy]];
        [self markAsDone:indexPath];
    }
}

#pragma mark  Helpers

- (BOOL)isTaskDone:(BuiltObject *)obj{
    return [[obj objectForKey:@"task_status"] boolValue];
}

- (BOOL)isStriked:(NSMutableAttributedString *)string{
    NSRange range = NSMakeRange(0, 1);
    if ([string attribute:NSStrikethroughStyleAttributeName atIndex:0 effectiveRange:&range]) {
        return YES;
    }
    return NO;
}

#pragma mark UIALertViewDelegate
-(void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex{
    if (buttonIndex != alertView.cancelButtonIndex) {
        [SVProgressHUD show];
        
        //create a new task
        BuiltClass *builtClass = [[AppDelegate sharedApplication].builtApplication classWithUID:@"todo_task"];
        BuiltObject *newTask = [builtClass object];
        [newTask setObject:[alertView textFieldAtIndex:0].text forKey:@"task_name"];
        
        BuiltACL *acl = [[AppDelegate sharedApplication].builtApplication acl];
        
        //No one else can view, edit or delete a user's tasks
        [acl setReadAccess:YES forUserId:[[AppDelegate sharedApplication].builtApplication currentUser].uid];
        [acl setWriteAccess:YES forUserId:[[AppDelegate sharedApplication].builtApplication currentUser].uid];
        [acl setDeleteAccess:YES forUserId:[[AppDelegate sharedApplication].builtApplication currentUser].uid];
        
        //only the user creating the task has permissions to view, edit or delete it
        [acl setPublicReadAccess:NO];
        [acl setPublicWriteAccess:NO];
        [acl setPublicDeleteAccess:NO];
        
        //set ACL
        [newTask setACL:acl];
        
        //save the task
        [newTask saveInBackgroundWithCompletion:^(ResponseType responseType, NSError *error) {
            if (!error) {
                [SVProgressHUD showSuccessWithStatus:@"Added!"];
                [self.objectCollection insertObject:newTask atIndex:0];
                
                NSIndexPath *indexpath = [NSIndexPath indexPathForRow:0 inSection:0];
                [self.tableView insertRowsAtIndexPaths:@[indexpath] withRowAnimation:UITableViewRowAnimationAutomatic];
            }
        }];
        
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
