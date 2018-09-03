class ListTest
{
    public static void main(String... args)
    {
        List<SectorUsage> list = new List<SectorUsage>();
       
        list.add(1, new SectorUsage(1,1));
        list.add(2, new SectorUsage(2,2));
        list.add(3, new SectorUsage(3,3));
        list.add(1, new SectorUsage(0,0));
       
        for(int i = 1; i <= list.size(); i++)
        {
            System.out.println(list.get(i).getStart());
        }
       
       list.remove(4);
        list.remove(1);
        list.remove(1);
       
        System.out.println();
       
        list.add(1, new SectorUsage(1,1));
        list.add(2, new SectorUsage(2,1));
        list.add(3, new SectorUsage(3,1));
       
        for(int i = 1; i <= list.size(); i++)
        {
            System.out.println(list.get(i).getStart());
        }
        return;
    }
}
