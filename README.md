# ESP32 bridge Serial2 to Bluethoot serial

Simple sketch to replicate a Serial2 connection (hardware serial) on a Bluetooth serial connection. For reliability the code uses buffers.

Application example for an e-bike battery with Smart-BMS SZLLT (same JBD / Xiaoxiang) and  PC app JBDtools.  
Work maybe also on Daly BMS with their PC soft ?? to be tested ...  
- Tested  with BMS SZLLT SP15S001-P13S-40A and JBDTools v.1.6

Discussion en français sur le [forum Cyclurba](https://cyclurba.fr/forum/forum_discussion.php?from=1&messageID=743774#msg743774)

---

### Diagram

<p align="left">
  <img src="./img/diagram_BMS_JBD.jpg" width="700" title="BMS JBD">
</p>

<p align="left">
  <img src="./img/diagram_esp32_pico.jpg" width="700" title="Pico">
</p>

my M5Stamp pico circuit. You can also use any ESP2 dev!   
Adapt RX and TX pins accordingly.   
**Note:** The DC-DC 55V-5V module is not used here: Unfortunately the 12V of the Smart-BMS does not provide enough current to power my EP32 BT!   
I put a strap to disable it in this case but use it for other applications, like [Bafang BBS_config](https://github.com/Chris741233/BBS_config)

<p align="left">
  <img src="./img/pico_circuit.jpg" width="700" title="Pico">
</p> 

<p align="left">
  <img src="./img/pico_and_ble.jpg" width="700" title="Pico and BLE">
</p> 

### How to use

On Windows associate the bluethoot device "ESP32_SMART_BMS" 
and locate the right com number ! (important) 

<p align="left">
  <img src="./img/connect_BT.jpg" width="500" title="connect BT">
</p>

in the JBDtools application (or other) specify the same com number and Bd (9600).  
click OK then start, and then wait for the connection to be established.   
Can sometimes take a little time, up to several seconds :exclamation:    
If it doesn't work check your serial Bluetooth com number.

<p align="left">
  <img src="./img/connect_JBD.jpg" width="500" title="connect JBD">
</p>

Connection successfully established! :wink:

<p align="left">
  <img src="./img/connect_JBD_2.jpg" width="500" title="connect JBD success">
</p>
