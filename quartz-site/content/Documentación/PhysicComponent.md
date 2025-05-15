Un PhysicComponent es una **clase abstracta** que, además de implementar los métodos que tiene un componente, implementa los métodos

- onCollisionEnter
- onCollisionExit
- onTriggerEnter
- onTriggerExit

y en cuyo ``init`` se suscriben estos eventos a una lista guardada en el [[RigidBody]] de la entidad que tenga este componente, utilizando el patrón de diseño **listener**. Estos eventos se llaman justo al final de la [[Simulación de físicas en Carom]].