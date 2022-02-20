import { AfterViewInit, Component, ElementRef, EventEmitter, Input, Output, ViewChild } from '@angular/core';
import { Reminder } from 'src/lib/data-access/models/reminder';


@Component({
  selector: 'reminder',
  templateUrl: './reminder.component.html',
  styleUrls: ['./reminder.component.scss'],
})
export class ReminderComponent implements AfterViewInit{
@Input() reminder?: Reminder;
@Input() selectedOnCreate: boolean;

@Output() onCheckboxPressed = new EventEmitter<number>();
@Output() flagged = new EventEmitter<Reminder>();
@Output() reminderChange = new EventEmitter<Reminder>();
@ViewChild('Date') myDate: ElementRef;
@ViewChild('Input') myInput: ElementRef;

showDeleteButton: boolean= false;
checkboxPressed: boolean = false;
startDate = new Date();


ngAfterViewInit(){
  if(this.selectedOnCreate){
    this.myInput.nativeElement.focus();
    this.myDate.nativeElement.focus();
  }
}
onCheckboxIsPressed(){
  if(this.checkboxPressed == true){
    this.checkboxPressed= false;
  }
  else{
    this.checkboxPressed = true;
    this.finalDeleteCheckbox();
  }
}
async finalDeleteCheckbox() {
  await this.delay(3000);
  if(this.checkboxPressed){
   this.onCheckboxPressed.emit(this.reminder.remId);
  }
}
delay(duration:number){
  return new Promise((resolve) => setTimeout(resolve, duration));
}
onMouseLeave(){
  this.showDeleteButton = false;
}
onMouseEnter(){
  this.showDeleteButton = true;
}

editValue(event:any){
  this.reminder.title = event.target.value;
  this.reminderChange.emit(this.reminder);
}
editDate(event:any){
  this.reminder.date = event.target.value;
  this.reminderChange.emit(this.reminder);
}
flagReminder(){
  this.reminder.flagged= !this.reminder.flagged;
  this.flagged.emit(this.reminder);
}
}
