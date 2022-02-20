import { HttpClientModule } from '@angular/common/http';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { MatNativeDateModule } from '@angular/material/core';
import { MatDatepickerModule } from '@angular/material/datepicker';
import { MatFormFieldModule } from '@angular/material/form-field';
import { MatInputModule } from '@angular/material/input';
import { BrowserModule } from '@angular/platform-browser';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { BoardComponent } from '../lib/feature/board/board.component';
import { ListComponent } from '../lib/feature/list/list.component';
import { ReminderComponent } from '../lib/feature/reminder/remindercomponent';
import { ToolbarComponent } from '../lib/ui/toolbar/toolbar.component';
import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';

@NgModule({
  declarations: [AppComponent, ToolbarComponent, BoardComponent, ListComponent, ReminderComponent],
  imports: [BrowserModule,FormsModule, AppRoutingModule, MatDatepickerModule, MatFormFieldModule, MatNativeDateModule, MatInputModule, BrowserAnimationsModule, HttpClientModule],
  providers: [],
  bootstrap: [AppComponent],
})
export class AppModule {}
