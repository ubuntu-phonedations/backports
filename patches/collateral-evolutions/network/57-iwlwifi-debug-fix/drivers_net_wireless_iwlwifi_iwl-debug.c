--- a/drivers/net/wireless/iwlwifi/iwl-debug.c
+++ b/drivers/net/wireless/iwlwifi/iwl-debug.c
@@ -139,8 +139,9 @@
 
 		va_copy(args2, args);
 		vaf.va = &args2;
-		dev_dbg(dev, "%c %s %pV", in_interrupt() ? 'I' : 'U',
-			function, &vaf);
+		dev_printk(KERN_DEBUG, dev, "%c %s %pV",
+			   in_interrupt() ? 'I' : 'U',
+			   function, &vaf);
 		va_end(args2);
 	}
 #endif