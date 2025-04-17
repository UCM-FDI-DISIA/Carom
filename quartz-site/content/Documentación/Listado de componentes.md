
## Resumen

En esta página se listan todos los componentes y una pequeña descripción de para que se usan, si los componentes pertenecen a un conjunto específico de funcionalidades se puede agrupar por clases padre (por ejemplo Render Component)

---
### Render Components
#### RenderSpritesheetComponent

Sirve para renderizar una imagen en base a unas filas y columnas asignadas en la creación del componente. Tiene funcionalidad para cambiar que casilla se renderiza

---

### Logic Component

#### AnimatorComponent

En base a la información en el struct auxiliar *Animation* va cambiando la casilla renderizada por el [[#RenderSpritesheetComponent]] de su entidad. Se puede acceder a las animaciones mediante sdlutils, las animaciones se escriben en resources. Todas las animaciones tienen un tipo que condiciona que ocurre cuando la termina (ver implementación de animation end).




