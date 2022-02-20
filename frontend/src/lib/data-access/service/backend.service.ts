import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { Board } from '../models/board';
import { List } from '../models/list';
import { Reminder } from '../models/reminder';

@Injectable({
  providedIn: 'root',
})
export class BackendService {
  readonly url: string = 'http://localhost:4200';

  constructor(private httpClient: HttpClient) {}

  loadBoard(): Observable<Board> {
    return this.httpClient.get<Board>(this.url + '/api/reminder');
  }

  createList(list: List): Observable<List> {
    let listPayload = {
      ...list,
    };

    return this.httpClient.post<List>(
      this.url + '/api/reminder/list',
      listPayload
    );
  }

  deleteList(id: number): Observable<void> {
    return this.httpClient.delete<void>(
      this.url + '/api/reminder/list/' + id
    );
  }

  updateList(list: Partial<List>): Observable<List> {
    let listPayload = {
      ...list,
    };

    return this.httpClient.put<List>(
      this.url + '/api/reminder/list/' + list.id,
      listPayload
    );
  }

  createReminder(id: number, reminder: Partial<Reminder>): Observable<Reminder> {
    let reminderPayload = {
      ...reminder,
    };

    return this.httpClient.post<Reminder>(
      this.url + '/api/reminder/list/' + id + '/reminder',
      reminderPayload
    );
  }

  deleteReminder(id: number, remId: number): Observable<void> {
    return this.httpClient.delete<void>(
      this.url + '/api/reminder/list/' + id + '/reminder/' + remId
    );
  }

  updateReminder(id: number, reminder: Partial<Reminder>): Observable<Reminder> {
    let reminderPayload = {
      ...reminder,
    };

    return this.httpClient.put<Reminder>(
      this.url + '/api/reminder/list/' + id + '/reminder/' + reminder.remId,
      reminderPayload
    );
  }
}
