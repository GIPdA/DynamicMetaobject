# Dynamic Qt Meta Objects


Small documented code example to test dynamic meta objects in Qt 5.

! Dependency to core-private is needed !


#### Random Notes:

- When using this with QML (as in the example), any meta objects added after the QML file/component is loaded will not be reflected on the QML side (the metaobject will not be "reloaded" as it should be static...).
- When adding a property, add a notify signal too or it will raise a QML error at runtime.
- Everything is not handled in this example.
- Don't forget to update the class name and super class when building with QMetaObjectBuilder.
- Lots of code is copy-pasted from generated moc file...


#### QVariant Data Pointers:
*Extracted from Qt Devs Days PDF, see below)*
- Returning values:

- Receiving values:
 - QVariant: `QVariant(typeid, argv[0])`.

- Properties:

- Calling Methods
 - Arguments:
 
 - Common task: turn `void**` arguments into a QVariantList 
  - *Never store argv itself, most likely invalid after you return!*
  
  - Determine its type id,

- Emitting Signals
 - `QMetaObject::activate(this, metaObject(), id, argv);`


#### Documentation:
https://www.qtdeveloperdays.com/sites/default/files/QtDevDays2014US-DIY-moc.pdf (a bit outdated, some things are wrong now, like base classe call in `qt_metacall`)

https://doc.qt.io/archives/qq/qq16-dynamicqobject.html (no QML but dynamic signal-slot connections)