# Open Ventilator
![Outside View](https://github.com/OpenVentilator/OpenVentilator/raw/master/media/render_outside_view.jpeg)
The open ventilator project was created in response to the demand for respirator created by the COVID-19 epidemic. The aim of the project is to create respiratory support device that can be quickly and easily produced with locally sourced material. The device is not a replacement for for respirators but in the event of a shortage of ventilators, these devices can provide support to patients that would otherwise not have any.

## Features

After consulting anesthesiologists, pulmonologists and biomedical engineers, we have settled for the below minimum feature set:

| Feature                                        | Values        |
|------------------------------------------------|---------------|
| Configurable Respiratory Rate (RR)             | 8-24 BPM      |
| Configurable Tidal Volume (TD)                 | Up to 600cc   |
| Configurable Fraction of Inhaled Oxygen (fio2) | Up to 100%    |
| Positive End Expiratory Pressure (PEEP)        | 1.5-20 H2O cm |
| Maximum Presspure                              | 4.0 kpa       |
| Airway Pressure Monitor                        | 0-60 cmH2Ox   |
| Exhaled air filtering                          | HEPA          |

Several documents have been published with similar specs, notably the [Rapidly manufactured ventilator system specification published by the Department of Health and Social Care in the UK](https://www.gov.uk/government/publications/coronavirus-covid-19-ventilator-supply-specification/rapidly-manufactured-ventilator-system-specification)


### Design Approach

Our approach was to reuse existing, tested and widely available technologies where possible. We also relied on previous research done notably at MIT and Rice University to develop our design.

We settled on a BVM based design based on their availabilty and familiarity and on the available add ons that provide many of the target features.


### Air Circuit
![Ventilator Diagram](https://github.com/OpenVentilator/OpenVentilator/raw/master/media/diagram.png)

The design in its current form implements a Mapleson A (Magill) breathing circuit. In order to achieve that, we moved the non rebreathing valve from the bag to the end of the tube. We have designed a 3D printed adaptor to connect the tube to the bag. 

### Board
To speed up go to market, we have reused an existing propriatory board we have in stock. Hence there are no schematics for the board in this repository. A dedicated open source board needs to be designed and published.

### Todo
- Publish images, renders and videos
- Publish BOM
- Design and publish logic board

### LICENSE

The design is released under a CERN Open Hardware License
