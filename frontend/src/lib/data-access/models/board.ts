import { List } from "./list";
export interface Board{
  title: string;
  Lists: List[];
  flagged: List;
  today: List;
}
