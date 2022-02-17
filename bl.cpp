//#include"include/bl.h"
//
//std::vector<Bobj> BL::GetAdressConnect(int sock, int dev_id)
//{
//    struct hci_conn_list_req *cl;
//    struct hci_conn_info *ci;
//
//    if (!(cl = (hci_conn_list_req *)malloc(10 * sizeof(*ci) + sizeof(*cl))))
//    {
//        perror("Can't allocate memory");
//        exit(1);
//    }
//    cl->dev_id = dev_id;
//    cl->conn_num = 10;
//    ci = cl->conn_info;
//
//    if (ioctl(sock, HCIGETCONNLIST, (void *)cl))
//    {
//        perror("Can't get connection list");
//        exit(1);
//    }
//    std::vector<Bobj> ad(cl->conn_num);
//    for (int i = 0; i < cl->conn_num; i++, ci++)
//    {
//        char addr[18];
//        char *str;
//        ad[i].SetMac(ci->bdaddr);
//        str = hci_lmtostr(ci->link_mode);
//
//        bt_free(str);
//    }
//
//    free(cl);
//    return std::move(ad);
//}
//std::vector<Bobj> BL::GetBobjConnect(int sock, int dev_id)
//{
//    std::vector<Bobj> bobj = GetAdressConnect(sock, dev_id);
//    for (int i = 0; i < bobj.size(); i++)
//    {
//        char addr2[248];
//        bdaddr_t *add = bobj[i].GetMac();
//        if (hci_read_remote_name(sock, add, 248,
//                                 addr2, 0) < 0)
//        {
//            perror("hci_read_remote_name");
//        }
//        bobj[i].SetName(addr2);
//    }
//    return std::move(bobj);
//}