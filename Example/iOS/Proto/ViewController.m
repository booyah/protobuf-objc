//
//  ViewController.m
//  Proto
//
//  Created by Will on 11/03/14.
//  Copyright (c) 2014 Will. All rights reserved.
//

#import "ViewController.h"

#import "NSObject+MKBlockTimer.h"
#import "ProtocolBuffers.h"
#import "Person.pb.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
//    [self proto];
//    [self json];
    
//    PersonBuilder *builder = [[PersonBuilder alloc] init];
//    [builder setPhoneTypesArray:@[@(PersonPhoneTypeHome),@(PersonPhoneTypeMobile)]];
//    [builder setPersonIdArray:@[[NSNumber numberWithLongLong:12323412],[NSNumber numberWithLongLong:11111111111]]];
//    Person *pp = [builder build];
//    NSLog(@"%lld",[pp.personId int64AtIndex:1]);

   //
//    PBArray *r = [array filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"self > 3.5"]];
//        [array enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
//            NSLog(@"%@", obj);
//        }];
//    NSLog(@"%@",r.firstObject);
    
    PersonBuilder *builder = [Person builder];
    
    NSArray *arr = @[[NSNumber numberWithUnsignedInteger:23],[NSNumber numberWithUnsignedInteger:25]];
    
    [builder setMyfieldArray:arr];
    
    Person *person = [builder build];
    
    
    NSAssert(([person.myfield uint32AtIndex:0] == [arr[0] unsignedIntegerValue]), @"NOT EQUALS");
    
    NSLog(@"%lu",[person.myfield uint32AtIndex:0]);
    
    
    
    Person *person2 = [Person parseFromData:person.data];
    
    NSLog(@"%lu",[person2.myfield uint32AtIndex:1]);
    
    
    
    if ([person.myfield uint32AtIndex:1] == [person2.myfield uint32AtIndex:1]) {
        
        NSLog(@"OK");
        
    }
    
    ExampleObjectBuilder *object1 = [ExampleObject builder];
    [object1 setExampleFieldArray:@[@2.2,@2.3]];
    ExampleObject *object =[object1 build];
    NSLog(@"%@",object);
//    
}


//-(void) proto
//{
//    // Proto Part
//    
//    NSLog(@"%@ %lu %lu %lu %lu",(sizeof(long) == 8 ? @"USING 64 bit system" : @"USING 32 bit system"),sizeof(int32_t), sizeof(long), sizeof(long long), sizeof(int64_t));
//    
//    NSData* raw_data = [NSData dataWithContentsOfURL:[NSURL URLWithString:@"http://0.0.0.0:4567/1/getGroups"]];
//    if (!raw_data)
//    {
//        NSLog(@"Please turn on the server");
//        return;
//    }
//    
//    __block Person* person;
//    NSLog(@"proto content size %@",[NSByteCountFormatter stringFromByteCount:raw_data.length countStyle:NSByteCountFormatterCountStyleMemory]);
//   
//    [NSObject logTime:^{
//        person = [Person parseFromData:raw_data];
//         NSLog(@"%ld",(long)person.personId);
//    } withPrefix:@"builing proto objects"];
//}
//
//-(void) json
//{
//    // JSON Part
//    NSData *raw_data = [NSData dataWithContentsOfURL:[NSURL URLWithString:@"http://192.168.2.1:4567/1/getGroupsJson"]];
//
//    if (!raw_data)
//    {
//        NSLog(@"Please turn on the server");
//        return;
//    }
//
//    NSLog(@" ");
//    NSLog(@"json content size %@",[NSByteCountFormatter stringFromByteCount:raw_data.length countStyle:NSByteCountFormatterCountStyleMemory]);
//    __block NSObject *serial;
//    [NSObject logTime:^{
//        serial = [NSJSONSerialization JSONObjectWithData:raw_data options:NSJSONReadingMutableContainers error:nil];
//    } withPrefix:@"parse json"];
//}


@end
