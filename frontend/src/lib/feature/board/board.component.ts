import { Component, OnInit } from '@angular/core';
import { Board } from 'src/lib/data-access/models/board';
import { List } from 'src/lib/data-access/models/list';
import { Reminder } from 'src/lib/data-access/models/reminder';
import { BackendService } from 'src/lib/data-access/service/backend.service';


@Component({
  selector: 'board',
  templateUrl: './board.component.html',
  styleUrls: ['./board.component.scss'],
})
export class BoardComponent implements OnInit{
  board: Board;
  selectedList?: List;
  selectedReminderList?: Reminder[];
  selectedReminder: Reminder;
  showFlagged: boolean = false;
  showToday: boolean = false;
  newListIndex?:number;
  newReminderIndex?:number;

  constructor(private backendService: BackendService){}

  ngOnInit(): void{
    this.backendService.loadBoard().subscribe((board)=>(this.board = board));
    if(this.board == null){
      this.board = {
      title:"Reminder",
      Lists: [
        {id:1, name:"to do", position: 0, reminders: [{remId: 7, title: "essen",position:0, date: new Date(), flagged:false}],length:1},
        {id:2, name: "hallo", position: 1, reminders:[{remId:8, title:"hallo", position:0, date: new Date(), flagged: false}], length: 1},
      ],
      flagged:{id: 10001, name:"Flagged", position: 1000, reminders:[], length:0},
      today: {id:10002, name:"Today", position:1001, reminders:[], length:0},
    }
  }
  else{
    this.addList();
  }
  for(let List of this.board.Lists){
    for(let Reminder of List.reminders){
        this.todayFilter(Reminder);
    }}
}

  selectList(list: List): void {
    this.selectedList= list;
    this.selectedReminderList=this.selectedList.reminders;
  }


  addList():void{
    const newList: List = {

      id: Math.random()*10000|0,
      name:"",
      position: 0,
      reminders: [],
      length: 0,
    };
    this.selectedList = newList;
    this.selectedReminderList= newList.reminders;

    this.newListIndex=this.board.Lists.push(newList)-1;
    newList.position= this.newListIndex === 0
      ? 1
      :this.board.Lists[this.newListIndex].position + 1;

    this.backendService.createList(newList).subscribe((list)=> {
      newList.id = list.id
      newList.position =list.position;
    });
  }

  addReminder(){
    const newReminder: Reminder={
      remId: Math.random()*10000|0,
      title:"",
      date: null,
      position: 0,
      flagged:false,
    }
    this.selectedReminder= newReminder;
    this.newReminderIndex =this.selectedReminderList.push(newReminder)-1;
    newReminder.position =
      this.newReminderIndex===0
        ? 1
        :this.selectedList.reminders[this.newReminderIndex - 1].position + 1;

    this.selectedList.length++;
    this.backendService.createReminder(this.selectedList.id, newReminder).subscribe((reminder)=> {
      newReminder.remId = reminder.remId;
      newReminder.position = reminder.position;
    });
  }

  deleteList(id:number){
    const index = this.board.Lists.findIndex((List)=> List.id === id);
    this.board.Lists.splice(index, 1);

    this.selectList(this.board.Lists[index-1]);

    this.backendService.deleteList(id).subscribe();
  }

  deleteReminder(id:number){

    const index = this.selectedList.reminders.findIndex((Reminder)=> Reminder.remId === id);
    const flagIndex = this.board.flagged.reminders.findIndex((Reminder)=> Reminder.remId===id);
    const todayIndex = this.board.today.reminders.findIndex((Reminder)=> Reminder.remId===id);
    if(flagIndex != -1 && this.selectedList != this.board.flagged){
        this.board.flagged.reminders.splice(index,1);
    }
    if(todayIndex != -1 && this.selectedList != this.board.today){
        this.board.today.reminders.splice(index,1);
    }
    this.selectedList.reminders.splice(index, 1);
    this.selectedList.length--;

    this.backendService.deleteReminder(this.selectedList.id, id).subscribe();
  }

  onShowFlagged(){
    this.selectedList= this.board.flagged;
  }

  onShowToday(){
    this.selectedList= this.board.today;
  }

  onReminderChange(reminder: Reminder){
    this.todayFilter(reminder);
    this.backendService.updateReminder(this.selectedList.id, reminder).subscribe();
  }

  todayFilter(reminder:Reminder){
    let date:string;
    var date_format = new Date();
    date = date_format.getMonth +'/'+ date_format.getDay+'/'+ date_format.getFullYear;
    let reminderDate = reminder.date.getMonth+'/'+reminder.date.getDay+'/'+reminder.date.getFullYear;
    if(reminderDate == date && this.board.today.reminders.indexOf(reminder) == -1){
      this.board.today.reminders.push(reminder);
    }
   }

  flagged(reminder:Reminder){
    const index = this.board.flagged.reminders.findIndex((Reminder)=> Reminder.remId === reminder.remId)
    if(index == -1){
        this.board.flagged.reminders.push(reminder);

    }
    else{
      this.board.flagged.reminders.splice(index,1);

    }
    this.backendService.updateReminder(this.selectedList.id, reminder).subscribe();
  }
}
