import { Component, ElementRef, EventEmitter, Input, Output, ViewChild } from '@angular/core';
import { List } from 'src/lib/data-access/models/list';
import { BackendService } from 'src/lib/data-access/service/backend.service';
@Component({
  selector: 'list',
  templateUrl: './list.component.html',
  styleUrls: ['./list.component.scss'],
})
export class ListComponent{
  @Input() list?: List;
  @Input() selectedOnCreate: boolean;
  @Output() deleteListEvent = new EventEmitter<number>();


  showDeleteButton:boolean = false;

  constructor(private backendService: BackendService) {}
  @ViewChild('myInput') myInput: ElementRef;



ngAfterViewInit(){
    this.myInput.nativeElement.focus();
  }
 onMouseEnter(){
   this.showDeleteButton = true;
 }
 onMouseLeave(){
   this.showDeleteButton = false;
 }
 onDeleteList(){
   this.deleteListEvent.emit(this.list.id);
 }
  editValue(event: any): void {
    this.list.name = event.target.value;
    this.backendService.updateList(this.list).subscribe();
  }
}
