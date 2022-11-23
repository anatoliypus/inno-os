dd if=/dev/zero of=lofs.img bs=1M count=55
sudo losetup /dev/loop8 lofs.img
mkfs -t ext4 lofs.img
mkdir lofsdisk
sudo mount /dev/loop8 ./lofsdisk/
sudo chmod 777 lofsdisk
