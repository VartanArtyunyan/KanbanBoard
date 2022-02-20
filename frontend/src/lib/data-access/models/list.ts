import { Reminder } from "./reminder";
export interface List{
  id?:number;
  name: string;
  position:number;
  length: number;
  reminders: Reminder[];

}
