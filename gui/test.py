from nicegui import app, ui

ui.textarea('This note is kept between visits').classes('w-full') \
    .bind_value(app.storage.user, 'note')

ui.run(storage_secret="asdiufjsadijfoiasdjfiosdajo")
