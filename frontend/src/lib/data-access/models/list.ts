import { Reminder } from "./reminder";
export interface List{
  id?:number;
  position:number;
  name: string;
  reminders: Reminder[];
  length: number;
}
