sudo insmod publisher.ko
sleep 2
sudo insmod grocery.ko
sleep 2
sudo insmod bookstand.ko
sleep 2
sudo insmod supermarket.ko

sleep 40

sudo rmmod supermarket.ko
sudo rmmod bookstand.ko
sudo rmmod grocery.ko
sudo rmmod publisher.ko 
