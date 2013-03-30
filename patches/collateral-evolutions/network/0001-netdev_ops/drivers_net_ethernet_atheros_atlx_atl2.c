--- a/drivers/net/ethernet/atheros/atlx/atl2.c
+++ b/drivers/net/ethernet/atheros/atlx/atl2.c
@@ -1396,7 +1396,7 @@
 
 	atl2_setup_pcicmd(pdev);
 
-	netdev->netdev_ops = &atl2_netdev_ops;
+	netdev_attach_ops(netdev, &atl2_netdev_ops);
 	atl2_set_ethtool_ops(netdev);
 	netdev->watchdog_timeo = 5 * HZ;
 	strncpy(netdev->name, pci_name(pdev), sizeof(netdev->name) - 1);