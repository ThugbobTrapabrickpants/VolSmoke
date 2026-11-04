// ============================================================================
// PROJECT: VolSmoke for BeamNG.drive.
// COPYRIGHT (C) 2026 REALSMOKE 3D CONTRIBUTORS.
// LICENSE: MIT (see LICENSE). Original project: https://github.com/ThugbobTrapabrickpants/VolSmoke
// ============================================================================
angular.module('beamng.apps')
.directive('realSmoke3DApp', [function () {
  return {
    templateUrl: '/ui/modules/apps/realSmoke3D/app.html',
    replace: true,
    restrict: 'EA',
    scope: true,
    link: function (scope, element) {
      function fitHostContainer() {
        try {
          var raw = element[0];
          if (!raw) return;
          var inner = (raw.classList && raw.classList.contains('real-smoke3d-container'))
            ? raw
            : (raw.querySelector ? raw.querySelector('.real-smoke3d-container') : raw);
          var h = inner ? inner.offsetHeight : 0;
          if (h > 0) {
            var cur = raw.parentElement;
            while (cur && cur.tagName !== 'BODY') {
              var isHostSlot = cur.classList.contains('bng-app') ||
                               cur.classList.contains('bng-app-content') ||
                               cur.classList.contains('ui-angular-app-slot') ||
                               cur.classList.contains('ui-app-host') ||
                               (cur.tagName && cur.tagName.toLowerCase() === 'bng-app');

              if (cur === raw.parentElement || isHostSlot) {
                cur.style.setProperty('height', h + 'px', 'important');
                cur.style.setProperty('min-height', '0px', 'important');
                cur.style.setProperty('background', 'transparent', 'important');
                cur.style.setProperty('box-shadow', 'none', 'important');
                cur.style.setProperty('border', 'none', 'important');
                cur.style.setProperty('overflow', 'hidden', 'important');
              }
              if (cur.classList.contains('ui-app-host') || cur.classList.contains('bng-app') || (cur.tagName && cur.tagName.toLowerCase() === 'bng-app')) {
                break;
              }
              cur = cur.parentElement;
            }
          }
        } catch (e) {}
      }

      scope.fitHostContainer = fitHostContainer;
      fitHostContainer();
      setTimeout(fitHostContainer, 50);
      setTimeout(fitHostContainer, 200);

      if (typeof ResizeObserver !== 'undefined') {
        var rawEl = element[0];
        var innerEl = rawEl ? ((rawEl.classList && rawEl.classList.contains('real-smoke3d-container'))
          ? rawEl
          : (rawEl.querySelector ? rawEl.querySelector('.real-smoke3d-container') : rawEl)) : null;
        if (innerEl) {
          var ro = new ResizeObserver(function () {
            fitHostContainer();
          });
          ro.observe(innerEl);
          scope.$on('$destroy', function () {
            ro.disconnect();
          });
        }
      }
    },
    controller: ['$log', '$scope', '$element', function ($log, $scope, $element) {
      const i18n = {
        ru: {
          appTitle: 'VolSmoke',
          author: 'open source',
          expand: 'Развернуть',
          collapse: 'Свернуть',
          toggleLang: 'Switch to English',
          diagEngineOk: '3D Engine: OK',
          diagEngineConnecting: '3D Engine: Ожидание автомобиля...',
          diagEngineFault: '3D Engine: ОФФЛАЙН (Нажмите для деталей)',
          diagErrorBadge: 'ОШИБКА ДИАГНОСТИКИ',
          diagFixTitle: 'КАК ИСПРАВИТЬ / РЕШЕНИЕ:',
          diagTitle_ERROR_ADDON_NOT_RESPONDING: 'ReShade без поддержки аддонов',
          diagMsg_ERROR_ADDON_NOT_RESPONDING: 'Установлен стандартный ReShade, который блокирует запуск .addon файлов.',
          diagFix_ERROR_ADDON_NOT_RESPONDING: 'Скачайте ReShade с официального сайта reshade.me по нижней кнопке («Download ReShade with full add-on support») и установите для BeamNG.drive.x64.exe. Стандартная версия блокирует аддоны для защиты от читов.',
          diagTitle_ERROR_VULKAN_INCOMPATIBLE: 'Игра запущена в режиме Vulkan',
          diagMsg_ERROR_VULKAN_INCOMPATIBLE: 'VolSmoke работает только на графическом API DirectX 11 / 12.',
          diagFix_ERROR_VULKAN_INCOMPATIBLE: 'Перезапустите BeamNG.drive в стандартном режиме (DirectX) через лаунчер игры.',
          diagTitle_ERROR_ADDON_MISSING_FROM_BIN64: 'Файл RealSmoke_3D.addon не найден',
          diagMsg_ERROR_ADDON_MISSING_FROM_BIN64: 'Файл нативного аддона отсутствует в папке игры Bin64.',
          diagFix_ERROR_ADDON_MISSING_FROM_BIN64: 'Скопируйте RealSmoke_3D.addon в папку игры Bin64 (рядом с исполняемым файлом BeamNG.drive.x64.exe).',
          diagTitle_ERROR_RESHADE_NOT_INSTALLED: 'ReShade не установлен',
          diagMsg_ERROR_RESHADE_NOT_INSTALLED: 'В папке Bin64 игры не обнаружены файлы ReShade (dxgi.dll / d3d11.dll).',
          diagFix_ERROR_RESHADE_NOT_INSTALLED: 'Установите ReShade с поддержкой аддонов для Bin64/BeamNG.drive.x64.exe.',
          diagTitle_ERROR_DEPTH_BUFFER_OFFLINE: 'Буфер глубины не перехвачен',
          diagMsg_ERROR_DEPTH_BUFFER_OFFLINE: 'ReShade не смог получить буфер глубины игры. Для безопасности дым скрыт.',
          diagFix_ERROR_DEPTH_BUFFER_OFFLINE: 'Отключите сторонние оверлеи (Discord, RivaTuner/MSI Afterburner, OBS Game Capture) или выберите правильный буфер глубины в оверлее ReShade (кнопка Home).',
          diagTitle_ERROR_HDR_LAYER_CONFLICT: 'Конфликт слоев HDR (D3D12)',
          diagMsg_ERROR_HDR_LAYER_CONFLICT: 'Внутриигровой режим HDR рассинхронизировал слой отрисовки интерфейса (CEF) и буфер кадра.',
          diagFix_ERROR_HDR_LAYER_CONFLICT: '1. Убедитесь, что в Windows включен HDR (Win+Alt+B).\\n2. В настройках графики BeamNG переключите режим экрана на "Полноэкранный" или "В окне без рамки".\\n3. Если проблема сохраняется, временно выключите HDR в графических настройках BeamNG или перезагрузите автомобиль (Ctrl+R).',
          diagTitle_ERROR_UI_LAYER_DESYNC: 'Конфликт оверлея интерфейса (CEF)',
          diagMsg_ERROR_UI_LAYER_DESYNC: 'Слой отрисовки интерфейса рассинхронизирован из-за внешнего оверлея или оконного режима.',
          diagFix_ERROR_UI_LAYER_DESYNC: '1. Отключите сторонние оверлеи (GeForce Experience, Discord, RivaTuner / RTSS).\n2. Переключите режим экрана в настройках BeamNG на "Полноэкранный" или "В окне без рамки".\n3. Перезагрузите автомобиль комбинацией Ctrl+R.',
          diagTitle_ERROR_DEPTH_SCALE_MISMATCH: 'Рассинхронизация масштаба Z-буфера',
          diagMsg_ERROR_DEPTH_SCALE_MISMATCH: 'Масштабирование апскейлера DLSS/FSR передало нулевой или недопустимый размер буфера глубины.',
          diagFix_ERROR_DEPTH_SCALE_MISMATCH: '1. Откройте "Настройки" -> "Графика" -> "Сглаживание".\n2. Переключите режим DLSS/FSR или сбросьте масштаб на 100% (DLAA), затем верните обратно на желаемый процент.\n3. Перезагрузите автомобиль (Ctrl+R).',
          diagTitle_ERROR_VERSION_MISMATCH: 'Несовпадение версий компонентов',
          diagMsg_ERROR_VERSION_MISMATCH: 'Версия нативного аддона (RealSmoke_3D.addon) не совпадает с установленным модом BeamNG.',
          diagFix_ERROR_VERSION_MISMATCH: 'Запустите autoinstall.bat (или install.bat) из папки релиза для синхронного обновления аддона и мода.',
          particleConflictTitle: 'Конфликт 2D-частиц (Не подавлен!)',
          particleConflictMsg: 'Сторонний мод переопределяет particles.json и вызывает появление плоских 2D-спрайтов. Подавление не удалось. Для чистой картинки удалите или отключите виновника:',
          reset: '↺ Сброс',
          resetTip: 'Сбросить все ползунки на сохранённые значения по умолчанию',
          wheelFL: 'FL Колесо',
          wheelFR: 'FR Колесо',
          wheelRL: 'RL Колесо',
          wheelRR: 'RR Колесо',
          slip: 'Срыв',
          smokeGenRate: 'Интенсивность дымовыделения',
          sectionTelemetry: 'Телеметрия 4 колес',
          sectionEquity: 'Подача дыма / Equity (Нагрев, Трение, Время)',
          heatThreshold: 'Порог нагрева шины',
          heatThresholdTip: 'Порог нагрева шины: Температурный порог пятна контакта для начала пиролиза резины. При значениях ниже порога резина еще не дымит. Позволяет точно настроить момент начала закипания шин.',
          heatThresholdMin: '40°C (Быстрый старт)',
          heatThresholdDef: '70°C (По умолч.)',
          heatThresholdMax: '120°C (Раскатка)',
          frictionSens: 'Чувствительность к силе трения',
          frictionSensTip: 'Чувствительность к силе трения: Множитель преобразования силы трения и скольжения протектора в плотность дыма. Увеличьте для мощного густого дыма даже при легком угле заноса.',
          frictionSensMin: '0.05x (Слабая)',
          frictionSensDef: '0.35x (По умолч.)',
          frictionSensMax: '3.0x (Агрессивная)',
          frictionTime: 'Время непрерывного трения',
          frictionTimeTip: 'Время непрерывного трения (Прогрев букса): Время непрерывного срыва колеса перед выходом на полную мощность дымовыделения. Предотвращает резкий выброс дыма при коротких пробуксовках и дает плавное нарастание при затяжном дрифте.',
          frictionTimeMin: '0.0s (Мгновенно)',
          frictionTimeDef: '2.00s (По умолч.)',
          frictionTimeMax: '3.0s (Затяжной прогрев)',
          smokeOnset: 'Нарастание дыма (Кривая Безье)',
          smokeOnsetTip: 'Нарастание дыма (Атака Безье): Время кубического сглаживания при начале пробуксовки. Устраняет резкий ступенчатый скачок дыма, создавая плавную кинематографичную подачу.',
          smokeOnsetBezier: 'S-Кривая появления дыма (Bézier)',
          smokeOnsetBezierTip: 'Кубическая S-кривая Безье определяет нарастание плотности дыма по мере нагрева протектора от порога (70°C) до критической температуры (220°C). Фоновая пунктирная линия отображает линейный рост температуры.',
          bezierAxisTemp: 'Температура шины (°C)',
          bezierAxisDensity: 'Плотность дыма (%)',
          bezierAxisDecayTime: 'Время рассеивания (с)',
          bezierAxisDecayDensity: 'Остаточный дым (%)',
          bezierStartTemp: 'Старт:',
          bezierInitialHaze: 'Дымка:',
          bezierEndTemp: 'Конец:',
          bezierMaxDensity: 'Макс:',
          smokeOnsetMin: '0.05s (Резко)',
          smokeOnsetDef: '2.00s (По умолч.)',
          smokeOnsetMax: '3.0s (Плавный разгон)',
          smokeDecayBezier: 'S-Кривая рассеивания остаточного дыма (Decay Bézier)',
          smokeDecayBezierTip: 'Кубическая S-кривая Безье определяет динамику рассеивания остаточного дыма горячих шин после прекращения пробуксовки или остановки колеса. Правая точка P3 задает длительность парения в секундах, а точки P1 и P2 формируют плавность затухания пара.',
          smokeDecay: 'Остаточный дым горячих шин',
          smokeDecayTip: 'Остаточный дым горячих шин (Шлейф остывания): Время, в течение которого раскаленная шина продолжает дымить после прекращения пробуксовки или остановки колеса.',
          smokeDecayMin: '0.0s (Резкий стоп)',
          smokeDecayDef: '1.00s (По умолч.)',
          smokeDecayMax: '5.0s (Долгое парение)',
          surfaceType: 'Покрытие',
          profileAsphalt: 'Асфальт (Пиролиз резины)',
          profileSand: 'Песок (Минеральная пыль)',
          profileAsphaltDesc: 'Термический пиролиз резины. Требует реального нагрева пятна контакта трением выше порога. Холодная передняя резина при качении не дымит.',
          profileSandDesc: 'Минерально-песчаная пыль. Поднимается от всех 4 колёс при срыве и вращении по песку. Не требует нагрева резины до 100°C.',
          sandDustScale: 'Плотность пыли песка',
          sandDustScaleTip: 'Плотность пыли песка: Множитель оптической плотности песчаного шлейфа при пробуксовке и движении по дюнам и песку.',
          sandDustScaleMin: '0.0x (Откл)',
          sandDustScaleDef: '1.00x (По умолч.)',
          sandDustScaleMax: '3.0x (Буря)',
          sandDustSens: 'Чувствительность срыва песка',
          sandDustSensTip: 'Чувствительность срыва песка: Скорость образования минеральной пыли при малейшей пробуксовке или качении по песчаному грунту.',
          sandDustSensMin: '0.05x (Плавная)',
          sandDustSensDef: '1.00x (По умолч.)',
          sandDustSensMax: '3.0x (Чуткая)',
          chipOn: 'ВКЛ',
          chipOff: 'ВЫКЛ',
          chipOnTip: 'Эффект активен. Нажмите, чтобы отключить (Mute) для проверки',
          chipOffTip: 'Эффект отключен (Mute). Нажмите, чтобы восстановить',
          sectionWheel: 'Дым у колеса (Плотность и рассеивание)',
          treadSaturation: 'Плотность у колеса',
          treadSaturationTip: 'Плотность у колеса (Насыщение): Мгновенная оптическая плотность дыма в точке трения шины об асфальт и на срезе арки. Позволяет дыму выходить сразу густым и непрозрачным без раздувания объема и размеров облака.',
          treadSatMin: '0.1x (Прозрачный)',
          treadSatDef: '1.00x (По умолч.)',
          treadSatMax: '7.0x (Густой/Молоко)',
          treadCoupling: 'Закручивание дыма вокруг колеса',
          treadCouplingTip: 'Закручивание дыма вокруг колеса: Регулирует силу передачи скорости вращения шины воздуху и увлечение дыма в колесную арку. При низких значениях дым стелется по асфальту; при высоких — мощный вихрь затягивает дым в арку и с силой выбрасывает наружу, взбивая клубы на дороге.',
          treadCoupMin: '0.05x (Мин. увлечение)',
          treadCoupDef: '0.50x (По умолч.)',
          treadCoupMax: '1.00x (Макс. увлечение)',
          edgeDispersion: 'Превращение в туман',
          edgeDispersionTip: 'Превращение в туман (Краевая дисперсия): Определяет, как быстро плотная дымка у колеса раскрывается по краям и переходит в мягкий туман на периферии. При малых значениях дым держится плотным сжатым жгутом, при высоких — быстро рассеивается в шелковистый туман уже возле колеса.',
          edgeDispMin: '0.10x (Плотный жгут)',
          edgeDispDef: '0.50x (По умолч.)',
          edgeDispMax: '2.50x (Широкое таяние)',
          sectionTurb: 'Физическая турбулентность (3 слоя симуляции)',
          turbTransition: 'Разбег вихрей (Дистанция)',
          turbTransitionTip: 'Дистанция нарастания турбулентности от 10% до 100% в метрах от колес (дефолт 0.8 м). Сглаживает существующую физику закрутки: прямо у покрышки дым выходит плотной струей, плавно раскрываясь в клубы на заданной дистанции. 0 м = мгновенные 100% вихри.',
          turbTransMin: '0.0 м (Мгновенно)',
          turbTransDef: '1.2 м (По умолч.)',
          turbTransMax: '12.0 м (Длинный)',
          turbRelax: 'Релаксация вихрей в туман (Время)',
          turbRelaxTip: 'Время жизни дыма до полного успокоения вихрей в спокойный туман (в секундах с момента выхода из-под колес). Позволяет свежему дыму бурно клубиться в первые 1-2 секунды, а затем плавно и органично переходить в гладкую диффузную дымку/туман без бесконечного дробления на мелкие неестественные спирали.',
          turbRelaxMin: '0.5s (Быстрое)',
          turbRelaxDef: '2.00s (По умолч.)',
          turbRelaxMax: '20.0s (Долгое)',
          subgroupMacro: 'Слой 1: Мелкие шероховатости (Фактура и завитки)',
          turbScale1: 'Масштаб 1: Размер шероховатостей',
          turbScale1Tip: 'Масштаб мелких шероховатостей: Пространственный масштаб фактуры и завивания струй дыма. Задает зернистость и детализацию первичных завихрений дыма.',
          turbScale1Min: '0.20x (Мелкий)',
          turbScale1Def: '1.05x (По умолч.)',
          turbScale1Max: '2.50x (Крупный)',
          turbStrength1: 'Сила 1: Закручивание шероховатостей',
          turbStrength1Tip: 'Сила мелких шероховатостей: Энергия закручивания и дробления дыма в живую фактуру.',
          turbStr1Min: '0.00x (Гладкий)',
          turbStr1Def: '1.30x (По умолч.)',
          turbStr1Max: '3.00x (Бурное кручение)',
          subgroupMicro: 'Слой 2: Крупные клубы (Рельеф и тени)',
          turbScale2: 'Масштаб 2: Размер крупных клубов',
          turbScale2Tip: 'Масштаб крупных клубов: Физический размер основных раскатистых бурунов и складок дыма (от 20 см до 80 см). Задает габариты и раскатистость объемных 3D-клубов.',
          turbScale2Min: '0.20x (Узкие клубы)',
          turbScale2Def: '0.75x (По умолч.)',
          turbScale2Max: '2.50x (Широкие клубы)',
          turbStrength2: 'Сила 2: Рельеф и глубина теней',
          turbStrength2Tip: 'Сила рельефа и теней: Выраженность крупных складок и глубина самозатенения в расщелинах между ними. Придает клубам контраст и четкий объемный 3D-рельеф.',
          turbStr2Min: '0.00x (Мягкий рельеф)',
          turbStr2Def: '1.00x (По умолч.)',
          turbStr2Max: '3.00x (Глубокий рельеф)',
          subgroupArch: 'Слой 3: Ротация в арках (Спиральные вихри)',
          turbArch: 'Ротация арок (Спирали)',
          turbArchTip: 'Спиральная ротационная турбулентность и вихревой срыв в арках колес. Придает выходящему дыму вращение по 3D-спирали с осевым выбросом наружу и срывом чередующихся противоположных вихрей при встрече со встречным потоком воздуха. Исключает эффект цельной колбасы и устраняет статичный выход дыма вверх («головой вверх»).',
          turbArchMin: '0.00x (Выкл)',
          turbArchDef: '2.00x (По умолч.)',
          turbArchMax: '8.00x (Бурная спираль)',
          turbArchScale: 'Масштаб ротации в арках',
          turbArchScaleTip: 'Масштаб вихрей в арках: Пространственный размер и радиус охвата спиральных вихрей, закручиваемых колесом в арке.',
          turbArchScaleMin: '0.20x (Узкий)',
          turbArchScaleDef: '0.25x (По умолч.)',
          turbArchScaleMax: '3.00x (Широкий)',
          sectionOptics: 'Калибровка фотореализма и оптики клубов',
          smokeColor: 'Цвет дыма: Палитра',
          smokeColorTip: 'Цвет дыма: Выбор физического оттенка и яркости дыма. По умолчанию установлен чистый физический белый (#FFFFFF). Нажмите на цветной прямоугольник для открытия окна палитры в стиле Photoshop.',
          smokeColorPickerTitle: 'Выбор цвета дыма',
          smokeColorDefaultBtn: 'По умолчанию (Белый)',
          smokeColorApplyBtn: 'Применить',
          smokeColorCancelBtn: 'Отмена',
          smokeColorCurrent: 'Текущий',
          smokeColorNew: 'Новый',
          dustColor: 'Цвет пыли и песка: Палитра',
          dustColorTip: 'Цвет пыли и песка: Выбор физического оттенка минеральной взвеси на песчаных и грунтовых трассах. По умолчанию установлен охристо-песчаный (#C2A680). Нажмите на цветной прямоугольник для открытия палитры.',
          dustColorPickerTitle: 'Выбор цвета песка и пыли',
          dustColorDefaultBtn: 'По умолчанию (Песочный)',
          colorDefaultBtn: 'По умолчанию',
          opticsTip: 'Калибровка оптики: Регулировка 3D-рельефа, глубины теней и плотности ядра для достижения фотографического сходства с реальным дымом.',
          hazeNormals: 'Нормали клубов: 3D Рельеф',
          hazeNormalsTip: 'Нормали клубов: Пространственный градиент плотности для освещения клубов дыма как 3D-поверхности с полу-Ламбертовым скульптурированием солнца и полусферой неба. (0.0x = плоский мыльный диск, 1.0x = объемные рельефные клубы).',
          hazeNormalsMin: '0.0x (Плоско)',
          hazeNormalsDef: '1.00x (По умолч.)',
          hazeNormalsMax: '2.50x (Рельеф)',
          creviceShadow: 'Тени в складках: Контраст',
          creviceShadowTip: 'Тени в складках: Снимает искусственный зажим эмбиента и углубляет затенение в узких расщелинах между клубами, увеличивая контрастность с 2.5:1 до >8:1. (0.0x = серая плоская дымка, 1.0x = глубокие тени и контрастные блики).',
          creviceShadowMin: '0.0x (Светло)',
          creviceShadowDef: '0.10x (По умолч.)',
          creviceShadowMax: '2.50x (Глубоко)',
          coreOpacity: 'Непрозрачность ядра: S-Кривая',
          coreOpacityTip: 'Непрозрачность ядра: Моделирует физическую конденсацию паров в микрокапли. Устраняет прозрачность дыма, превращая плотный центр в непроницаемую белую массу, закрывающую машину и фон. (0.0x = прозрачный туман, 1.0x = плотный монолит).',
          coreOpacityMin: '0.0x (Туман)',
          coreOpacityDef: '1.00x (По умолч.)',
          coreOpacityMax: '3.00x (Монолит)',
          vorticityDetail: 'Микровихри: Текстура складок',
          vorticityDetailTip: 'Микровихри: Добавляет высокочастотную текстуру завихрений вдоль границы струи, устраняя воксельное размытие. (0.0x = гладкий воксель, 1.0x = мелкие клубы и складки).',
          vorticityDetailMin: '0.0x (Гладко)',
          vorticityDetailDef: '1.00x (По умолч.)',
          vorticityDetailMax: '2.50x (Текстура)',
          sectionTrail: 'Шлейф и динамика рассеивания',
          coreLifetime: 'Живучесть шлейфа',
          coreLifetimeTip: 'Живучесть шлейфа: Замедляет рассеивание плотного ядра зрелого дыма (4-6 сек), продлевая длину видимого дымового хвоста позади автомобиля на несколько корпусов.',
          coreLifeMin: '0.05x (Быстро тает)',
          coreLifeDef: '0.25x (По умолч.)',
          coreLifeMax: '2.50x (Долгий хвост)',
          dispersionRate: 'Скорость рассеивания шлейфа',
          dispersionRateTip: 'Скорость рассеивания зрелого шлейфа: Управляет тем, как быстро тает зрелый дым вдалеке от автомобиля. Дым у колес сохраняет полную плотность, а хвост шлейфа растворяется быстрее при высоких значениях.',
          dispRateMin: '0.20x (Долгий шлейф)',
          dispRateDef: '0.40x (По умолч.)',
          dispRateMax: '3.00x (Быстрое таяние)',
          underbodyEject: 'Выброс из-под днища',
          underbodyEjectTip: 'Выброс из-под днища: Мощность воздушной струи под днищем автомобиля, выдувающей дым назад через диффузор при пробуксовке.',
          underbodyEjectMin: '0.0x (Выкл)',
          underbodyEjectDef: '0.20x (По умолч.)',
          underbodyEjectMax: '3.0x (Мощный)',
          archEject: 'Выброс из арок',
          archEjectTip: 'Выброс из арок: Скорость воздушной струи, выбрасывающей дым сверху вниз через колесные арки на асфальт.',
          archEjectMin: '0.0x (Выкл)',
          archEjectDef: '0.15x (По умолч.)',
          archEjectMax: '3.00x (Макс)',
          roadDamping: 'Сцепка с асфальтом',
          roadDampingTip: 'Сцепка с асфальтом: Вязкое торможение дыма в приземном слое (до 25 см от асфальта). Предотвращает неестественное скольжение воздуха за машиной и прижимает нижний край шлейфа к дороге.',
          roadDampMin: '0.0x (Скользит)',
          roadDampDef: '0.55x (По умолч.)',
          roadDampMax: '5.0x (Липкий)',
          smokeDrag: 'Встречный поток (Торможение воздухом)',
          smokeDragTip: 'Встречный поток (Торможение воздухом): Глобальное аэродинамическое торможение дымки о неподвижный стоячий воздух в открытом пространстве вне воздушного кармана с генерацией 3D-турбулентности и клубящихся вихрей сдвига. Управляет степенью агрессивности замедления дыма.',
          smokeDragMin: '0.0x (Без торможения)',
          smokeDragDef: '0.15x (По умолч.)',
          smokeDragMax: '3.0x (Быстрое торможение)',
          sectionSlipstream: '6. Воздушный карман и 3D-турбулентность',
          slipstream: 'Сила удержания кармана (slipstream)',
          slipstreamTip: 'Сила аэродинамического кармана разряжения позади кузова. Задерживает дым в зоне низкого давления за автомобилем независимо от направления движения (вперед, назад, боком) и плавно отпускает его назад.',
          slipstreamMin: '0.00x (Без кармана)',
          slipstreamDef: '0.75x (По умолч.)',
          slipstreamMax: '2.50x (Сильный захват)',
          slipstreamSpeedLimit: 'Лимит скорости задержки дыма',
          slipstreamSpeedLimitTip: 'Предельная разница скоростей между автомобилем и шлейфом. Не позволяет дыму отставать от автомобиля быстрее указанного значения (км/ч), исключая эффект гармошки на высокой скорости.',
          slipstreamSpeedLimitMin: '30 км/ч (Плотная сцепка)',
          slipstreamSpeedLimitDef: '50 км/ч (По умолч.)',
          slipstreamSpeedLimitMax: '360 км/ч (Свободный срыв)',
          slipstreamHoldTime: 'Время удержания шлейфа',
          slipstreamHoldTimeTip: 'Длительность удержания шлейфа в воздушном мешке позади автомобиля (в миллисекундах) перед плавным сходом в открытую атмосферу.',
          slipstreamHoldTimeMin: '100 мс (Быстрый срыв)',
          slipstreamHoldTimeDef: '200 мс (По умолч.)',
          slipstreamHoldTimeMax: '2000 мс (Долгий карман)',
          slipstreamBezier: 'S-Кривая схода шлейфа',
          slipstreamBezierTip: 'Аэродинамический карман за автомобилем: задает профиль схода дыма из зоны разрежения за кузовом. Ось X — прогресс времени удержания (0%..100%). Ось Y — процент связки со скоростью машины (100%..0%). P1 настраивает мягкость отрыва от бампера, P2 — плавность рассеивания в атмосфере.',
          bezierAxisSlipTime: 'Прогресс удержания (время)',
          bezierAxisSlipHold: 'Удержание за машиной (%)',
          bezierPresetSmooth: 'Плавная S',
          bezierPresetProgressive: 'Прогрессивная',
          bezierPresetAggressive: 'Агрессивная',
          bezierPresetLingering: 'Затяжная',
          bezierPresetFast: 'Быстрый срыв',
          bezierPresetLinear: 'Линейная',
          slipstreamTurbScale: 'Размер вихрей 3D-турбулентности',
          slipstreamTurbScaleTip: 'Пространственный масштаб вихрей 3D curl noise в воздушном кармане. Меньше = мелкие вихревые клубы, больше = крупные раскатистые вихревые массы.',
          slipstreamTurbScaleMin: '0.20x (Мелкие вихри)',
          slipstreamTurbScaleDef: '0.30x (По умолч.)',
          slipstreamTurbScaleMax: '3.00x (Крупные клубы)',
          slipstreamTurbStrength: 'Сила 3D-турбулентности кармана',
          slipstreamTurbStrengthTip: 'Скорость вихревого перемешивания 3D curl noise в кармане разряжения. Интенсивно смешивает дым от обоих колес в единую клубящуюся массу без лобовых столкновений и без вертикального подъема.',
          slipstreamTurbStrengthMin: '0.00x (Выкл)',
          slipstreamTurbStrengthDef: '0.50x (По умолч.)',
          slipstreamTurbStrengthMax: '3.00x (Мощный вихрь)',
          debugWakeModeTitle: '3D-Визуализатор кармана (Debug)',
          debugWakeModeTip: 'Отображает трехмерную границу воздушного кармана (бирюзовый изо-объем с Френелем) и динамические векторы течений (желтый восходящий вихрь у бампера, втягивание внутрь и уходящий след). Позволяет вживую откалибровать геометрию кармана на любом автомобиле.',
          wakeModeOff: 'Обычный дым',
          wakeModeBubble: '3D-Пузырь',
          wakeModeFlow: 'Пузырь + Течения',
          thermalBuoyancy: 'Тепловая плавучесть',
          thermalBuoyancyTip: 'Тепловая плавучесть (Архимед): Подъемная сила горячего дыма. Определяет, как сильно шлейф тянет вверх после отрыва от машины. Убавьте (например, до 0.2x–0.5x), чтобы дым стелился горизонтально позади машины и не улетал в небо через 2 секунды.',
          thermalBuoyMin: '0.0x (Горизонтально)',
          thermalBuoyDef: '0.10x (По умолч.)',
          thermalBuoyMax: '1.0x (Взмывает вверх)',
          sectionGrid: '7. Рендеринг и воксельная сетка GPU',
          raymarchQuality: 'Качество лучей',
          qualityMin: '1.0x (Быстро)',
          qualityBal: '2.0x (Найквист / Четко)',
          qualityMax: '5.0x (Макс)',
          voxelSize: 'Размер вокселя',
          voxelMin: '40 mm (Ультра)',
          voxelDrift: '64 mm (Дрифт)',
          voxelMax: '100 mm (Быстро)',
          domainSize: 'Размер бокса (Горизонталь)',
          domainSizeTip: 'Размер бокса (Горизонталь): Физическая протяженность рабочей зоны симуляции по осям X и Y (от 6.0 до 70.0 м). Изменяет границы симуляции без изменения размера вокселей (сетка масштабируется пропорционально).',
          domainMin: '6.0 м',
          domainDef: '13.5 м (По умолч.)',
          domainMax: '70.0 м',
          toggleHint: 'Клавиша меню: Insert / F7',
          navierStokes: 'Navier-Stokes',
          presetDefault: 'Дефолтный',
          presetTitle: 'Пресеты настроек',
          presetSlots: 'Слоты',
          presetLimitNotice: 'Достигнут лимит (10/10 пресетов).',
          presetSandboxNotice: 'Экспериментальный режим: Лимит (10/10 пресетов) исчерпан. Изменения активны в игре, но не сохранятся, пока вы не выберете или не освободите один из пресетов.',
          presetAddBtn: 'Добавить пресет (+)',
          presetDuplicateBtn: 'Дублировать пресет (❐)',
          presetDeleteBtn: 'Удалить пресет',
          presetRenameBtn: 'Переименовать пресет',
          presetDuplicateWord: 'Дублировать',
          presetAddWord: 'Создать',
          presetRenameWord: 'Переименовать',
          presetDeleteWord: 'Удалить',
          resetWord: 'Сбросить',
          resetSectionTip: 'Сбросить параметры этой секции на значения по умолчанию',
          presetLimitReached: 'Лимит (10/10)',
          presetNamePlaceholder: 'Имя пресета',
          slipstreamBetaTitle: 'Экспериментальный режим (BETA)',
          slipstreamBetaDesc: 'Физика воздушного кармана находится в стадии ранней калибровки и может работать нестабильно. В будущих версиях механика удержания и вихри будут улучшены.',
          gpuLoadWarn: 'Высокая нагрузка на GPU: Объём сетки — ',
          gpuLoadWarnSuffix: ' млн вокселей (> 5 млн). Возможно снижение FPS.',
        },
        en: {
          appTitle: 'VolSmoke',
          author: 'open source',
          expand: 'Expand',
          collapse: 'Collapse',
          toggleLang: 'Переключить на Русский',
          diagEngineOk: '3D Engine: OK',
          diagEngineConnecting: '3D Engine: Waiting for vehicle...',
          diagEngineFault: '3D Engine: OFFLINE (Click for details)',
          diagErrorBadge: 'DIAGNOSTIC ALERT',
          diagFixTitle: 'ACTIONABLE RESOLUTION:',
          diagTitle_ERROR_ADDON_NOT_RESPONDING: 'ReShade lacks Add-on support',
          diagMsg_ERROR_ADDON_NOT_RESPONDING: 'Standard ReShade is installed, which blocks all .addon files.',
          diagFix_ERROR_ADDON_NOT_RESPONDING: 'Download ReShade from official website reshade.me using the bottom button ("Download ReShade with full add-on support") and reinstall for BeamNG.drive.x64.exe. The standard version disables addons for anti-cheat protection.',
          diagTitle_ERROR_VULKAN_INCOMPATIBLE: 'Game running in Vulkan mode',
          diagMsg_ERROR_VULKAN_INCOMPATIBLE: 'VolSmoke strictly requires DirectX 11 or DirectX 12.',
          diagFix_ERROR_VULKAN_INCOMPATIBLE: 'Relaunch BeamNG.drive in standard DirectX mode from the game launcher.',
          diagTitle_ERROR_ADDON_MISSING_FROM_BIN64: 'RealSmoke_3D.addon missing from Bin64',
          diagMsg_ERROR_ADDON_MISSING_FROM_BIN64: 'Native addon binary is not in the game Bin64 folder.',
          diagFix_ERROR_ADDON_MISSING_FROM_BIN64: 'Copy RealSmoke_3D.addon into your game Bin64 folder (next to BeamNG.drive.x64.exe).',
          diagTitle_ERROR_RESHADE_NOT_INSTALLED: 'ReShade not detected in game folder',
          diagMsg_ERROR_RESHADE_NOT_INSTALLED: 'Neither dxgi.dll nor d3d11.dll was found in Bin64.',
          diagFix_ERROR_RESHADE_NOT_INSTALLED: 'Install ReShade with full add-on support for Bin64/BeamNG.drive.x64.exe.',
          diagTitle_ERROR_DEPTH_BUFFER_OFFLINE: 'Depth buffer unavailable',
          diagMsg_ERROR_DEPTH_BUFFER_OFFLINE: 'ReShade cannot capture the scene depth buffer. Smoke is hidden for safety.',
          diagFix_ERROR_DEPTH_BUFFER_OFFLINE: 'Disable conflicting overlays (Discord, RivaTuner, OBS Game Capture) or select the active depth buffer in ReShade overlay (Home key).',
          diagTitle_ERROR_HDR_LAYER_CONFLICT: 'HDR Layer Conflict (D3D12)',
          diagMsg_ERROR_HDR_LAYER_CONFLICT: 'In-game HDR mode desynchronized the CEF user interface layer and framebuffer composite.',
          diagFix_ERROR_HDR_LAYER_CONFLICT: '1. Verify Windows HDR is enabled (Win+Alt+B).\\n2. In BeamNG Graphics Settings, switch display mode to "Fullscreen" or "Borderless Window".\\n3. If smoke remains hidden, temporarily toggle HDR in BeamNG settings or reload vehicle (Ctrl+R).',
          diagTitle_ERROR_UI_LAYER_DESYNC: 'Interface Layer Desync (CEF)',
          diagMsg_ERROR_UI_LAYER_DESYNC: 'UI composite layer desynchronized due to an external overlay or window display mode.',
          diagFix_ERROR_UI_LAYER_DESYNC: '1. Disable third-party overlays (GeForce Experience, Discord, RivaTuner / RTSS).\n2. Switch display mode in BeamNG Graphics Settings to "Fullscreen" or "Borderless Window".\n3. Reload vehicle with Ctrl+R.',
          diagTitle_ERROR_DEPTH_SCALE_MISMATCH: 'Depth Buffer Scale Mismatch',
          diagMsg_ERROR_DEPTH_SCALE_MISMATCH: 'DLSS/FSR upscaler reported invalid or zero depth buffer dimensions.',
          diagFix_ERROR_DEPTH_SCALE_MISMATCH: '1. Open BeamNG Graphics Settings -> Anti-Aliasing.\n2. Toggle DLSS/FSR mode or reset scale to 100% (DLAA), then re-apply desired preset.\n3. Reload vehicle with Ctrl+R.',
          diagTitle_ERROR_VERSION_MISMATCH: 'Component Version Mismatch',
          diagMsg_ERROR_VERSION_MISMATCH: 'Native add-on version (RealSmoke_3D.addon) does not match the installed BeamNG mod version.',
          diagFix_ERROR_VERSION_MISMATCH: 'Run autoinstall.bat (or install.bat) from the release folder to synchronously update both the add-on and mod.',
          particleConflictTitle: '2D Particle Conflict (Unsuppressed!)',
          particleConflictMsg: 'A third-party mod overrides particles.json causing flat 2D sprites to leak through. Suppression failed. To ensure visual fidelity, remove or disable the conflicting mod:',
          reset: '↺ Reset',
          resetTip: 'Reset all sliders to saved defaults',
          wheelFL: 'FL Wheel',
          wheelFR: 'FR Wheel',
          wheelRL: 'RL Wheel',
          wheelRR: 'RR Wheel',
          slip: 'Slip',
          smokeGenRate: 'Smoke Generation Rate',
          sectionTelemetry: '4-Wheel Telemetry',
          sectionEquity: 'Smoke Emission Equity (Heat, Friction, Duration)',
          heatThreshold: 'Tire Heat Threshold',
          heatThresholdTip: 'Tire Heat Threshold: Contact patch temperature threshold for rubber pyrolysis. Below this threshold, tires do not emit smoke, allowing you to fine-tune when burnout smoke kicks off.',
          heatThresholdMin: '40°C (Instant)',
          heatThresholdDef: '70°C (Default)',
          heatThresholdMax: '120°C (High Heat)',
          frictionSens: 'Friction & Slip Sensitivity',
          frictionSensTip: 'Friction & Slip Sensitivity: Multiplier for slip force and friction work converted into smoke density. Increase for aggressive thick smoke during light drifts.',
          frictionSensMin: '0.05x (Low)',
          frictionSensDef: '0.35x (Default)',
          frictionSensMax: '3.0x (Aggressive)',
          frictionTime: 'Sustained Friction Duration',
          frictionTimeTip: 'Sustained Friction Duration: Continuous wheel slip duration before full smoke emission ramps up. Prevents jarring instantaneous smoke bursts on brief wheelspin, creating smooth progression during sustained burnouts and drifts.',
          frictionTimeMin: '0.0s (Instant)',
          frictionTimeDef: '2.00s (Default)',
          frictionTimeMax: '3.0s (Long Build-up)',
          smokeOnset: 'Bézier Smoke Attack',
          smokeOnsetTip: 'Bézier Smoke Attack: Cubic easing attack duration when wheel slip begins. Replaces jarring step-function smoke burst with realistic smooth build-up.',
          smokeOnsetBezier: 'Smoke Onset S-Curve (Bézier)',
          smokeOnsetBezierTip: 'Cubic Bézier S-curve determines the growth of smoke density as the tire tread heats from the threshold (70°C) to critical temperature (220°C). The dashed background line displays linear temperature growth.',
          bezierAxisTemp: 'Tire Temperature (°C)',
          bezierAxisDensity: 'Smoke Density (%)',
          bezierAxisDecayTime: 'Dissipation Time (s)',
          bezierAxisDecayDensity: 'Residual Smoke (%)',
          bezierStartTemp: 'Start:',
          bezierInitialHaze: 'Haze:',
          bezierEndTemp: 'End:',
          bezierMaxDensity: 'Max:',
          smokeOnsetMin: '0.05s (Sharp)',
          smokeOnsetDef: '2.00s (Default)',
          smokeOnsetMax: '3.0s (Smooth Build)',
          smokeDecayBezier: 'Hot-Tire Residual Decay S-Curve (Bézier)',
          smokeDecayBezierTip: 'Cubic Bézier S-curve determines the dissipation dynamics of lingering hot-tire smoke once wheel spin or sliding ceases. Handle P3 sets dissipation duration in seconds, while P1 and P2 shape the fade curvature.',
          smokeDecay: 'Hot-Tire Residual Decay',
          smokeDecayTip: 'Hot-Tire Residual Decay: Duration over which pyrolyzing hot rubber continues emitting smoke after wheel slip ceases or the car stops.',
          smokeDecayMin: '0.0s (Instant Stop)',
          smokeDecayDef: '1.00s (Default)',
          smokeDecayMax: '5.0s (Lingering Steam)',
          surfaceType: 'Surface',
          profileAsphalt: 'Asphalt (Rubber Pyrolysis)',
          profileSand: 'Sand (Mineral Dust)',
          profileAsphaltDesc: 'Thermal rubber pyrolysis smoke. Requires authentic friction heat above threshold. Cold rolling tires never emit smoke.',
          profileSandDesc: 'Mineral sand dust. Kicks up from all 4 wheels upon ground shear and wheel spin. Does not require heating rubber to 100°C.',
          sandDustScale: 'Sand Dust Density',
          sandDustScaleTip: 'Sand Dust Density: Optical density multiplier for the sand dust plume during wheel spin or driving over sandy terrain.',
          sandDustScaleMin: '0.0x (Off)',
          sandDustScaleDef: '1.00x (Default)',
          sandDustScaleMax: '3.0x (Dense)',
          sandDustSens: 'Sand Slip Sensitivity',
          sandDustSensTip: 'Sand Slip Sensitivity: Rate of mineral dust kick-up at light wheel slip or rolling speeds across sand.',
          sandDustSensMin: '0.05x (Gentle)',
          sandDustSensDef: '1.00x (Default)',
          sandDustSensMax: '3.0x (Eager)',
          chipOn: 'ON',
          chipOff: 'OFF',
          chipOnTip: 'Effect active. Click to mute/bypass for isolated A/B testing',
          chipOffTip: 'Effect bypassed (Muted). Click to re-enable',
          sectionWheel: 'Wheel Smoke (Density & Dispersion)',
          treadSaturation: 'Tread Saturation',
          treadSaturationTip: 'Tread Saturation: Instant optical density of smoke at tire contact patch and wheel arch exit. Allows dense, opaque smoke without inflating cloud volume.',
          treadSatMin: '0.1x (Sheer)',
          treadSatDef: '1.00x (Default)',
          treadSatMax: '7.0x (Dense/Opaque)',
          treadCoupling: 'Wheel Smoke Wrapping',
          treadCouplingTip: 'Wheel Smoke Wrapping: Regulates transfer of tire rotation speed to surrounding air and smoke entrainment into the wheel arch. At low values smoke drifts along asphalt; at high values a powerful vortex pulls smoke into the arch and violently discharges billows onto the road.',
          treadCoupMin: '0.05x (Min)',
          treadCoupDef: '0.50x (Default)',
          treadCoupMax: '1.00x (Max)',
          edgeDispersion: 'Transformation into Fog',
          edgeDispersionTip: 'Transformation into Fog (Edge Dispersion): Controls how quickly dense smoke expands and turns into soft fog at perimeter. Low values keep a tight rope; high values create a wide, soft mist right around tires.',
          edgeDispMin: '0.10x (Tight Plume)',
          edgeDispDef: '0.50x (Default)',
          edgeDispMax: '2.50x (Wide Mist)',
          sectionTurb: 'Physical Turbulence (3 Simulation Layers)',
          turbTransition: 'Vortex Growth Distance',
          turbTransitionTip: 'Fixed distance in meters from tires where existing turbulence smoothly ramps up from 10% to 100% (default 0.8m). Smoke leaves the tire as a compact laminar jet, blossoming into rolling billows at distance. 0m = instant 100% vortices.',
          turbTransMin: '0.0 m (Instant)',
          turbTransDef: '1.2 m (Default)',
          turbTransMax: '12.0 m (Long)',
          turbRelax: 'Vortex Relaxation Time',
          turbRelaxTip: 'Physical smoke lifetime before vorticity confinement forces smoothly dissipate into calm diffuse mist/fog (in seconds since emission). Gives fresh smoke initial violent rolling freedom in the first 1-2 seconds, followed by smooth laminar settling instead of degrading into artificial micro-spirals.',
          turbRelaxMin: '0.5s (Fast Calm)',
          turbRelaxDef: '2.00s (Default)',
          turbRelaxMax: '20.0s (Long Churn)',
          subgroupMacro: 'Layer 1: Fine Texture (Surface Eddies & Curls)',
          turbScale1: 'Scale 1: Fine Texture Scale',
          turbScale1Tip: 'Scale of fine turbulent eddies: Spatial frequency of surface texture and curls.',
          turbScale1Min: '0.20x (Fine)',
          turbScale1Def: '1.05x (Default)',
          turbScale1Max: '2.50x (Coarse)',
          turbStrength1: 'Strength 1: Fine Eddy Swirl',
          turbStrength1Tip: 'Energy of fine surface texture and swirling eddies.',
          turbStr1Min: '0.00x (Smooth)',
          turbStr1Def: '1.30x (Default)',
          turbStr1Max: '3.00x (Vigorous)',
          subgroupMicro: 'Layer 2: Large Billows (Relief & Depth)',
          turbScale2: 'Scale 2: Large Billow Radius',
          turbScale2Tip: 'Scale of large rolling billows: Physical radius of cumulus plume lobes.',
          turbScale2Min: '0.20x (Narrow)',
          turbScale2Def: '0.75x (Default)',
          turbScale2Max: '2.50x (Broad)',
          turbStrength2: 'Strength 2: Billow Relief & Depth',
          turbStrength2Tip: 'Depth and contrast of large billow folds and crevices.',
          turbStr2Min: '0.00x (Soft Relief)',
          turbStr2Def: '1.00x (Default)',
          turbStr2Max: '3.00x (Deep Relief)',
          subgroupArch: 'Layer 3: Arch Rotation (Spiral Vortices)',
          turbArch: 'Arch Rotation (Spirals)',
          turbArchTip: 'Spiral rotational turbulence and vortex breakdown in wheel arches. Imparts 3D helical corkscrew swirl with outward axial ejection and alternating shear shedding against oncoming airflow. Prevents solid cylinder ("sausage") artifacts and eliminates passive straight-up smoke emergence.',
          turbArchMin: '0.00x (Off)',
          turbArchDef: '2.00x (Default)',
          turbArchMax: '8.00x (Intense Spiral)',
          turbArchScale: 'Arch Vortex Scale',
          turbArchScaleTip: 'Arch Vortex Scale: Spatial radius and reach of spiral vortices created by wheels inside the wheel arches.',
          turbArchScaleMin: '0.20x (Compact)',
          turbArchScaleDef: '0.25x (Default)',
          turbArchScaleMax: '3.00x (Broad)',
          sectionOptics: 'Photorealism & Billow Optics Calibration',
          smokeColor: 'Smoke Color: Palette',
          smokeColorTip: 'Smoke Color: Select the physical tint and brightness of tire smoke. Defaults to pure physical white (#FFFFFF). Click the color swatch to open the Photoshop-style palette.',
          smokeColorPickerTitle: 'Select Smoke Color',
          smokeColorDefaultBtn: 'Default (White)',
          smokeColorApplyBtn: 'Apply',
          smokeColorCancelBtn: 'Cancel',
          smokeColorCurrent: 'Current',
          smokeColorNew: 'New',
          dustColor: 'Sand & Dust Color: Palette',
          dustColorTip: 'Sand & Dust Color: Select the physical tint of mineral dust on sandy and dirt tracks. Defaults to sandy ochre (#C2A680). Click the color swatch to open the palette.',
          dustColorPickerTitle: 'Select Sand & Dust Color',
          dustColorDefaultBtn: 'Default (Sand)',
          colorDefaultBtn: 'Default',
          opticsTip: 'Optics calibration: Dial in 3D billow relief, shadow contrast, and plume core opacity to match real-life burnout references.',
          hazeNormals: 'Billow Normals: 3D Relief',
          hazeNormalsTip: 'Billow Normals: Evaluates spatial density gradients to sculpt smoke lobes towards sunlight with Half-Lambert wrap and hemisphere ambient. (0.0x = flat blur, 1.0x = 3D cauliflower billows).',
          hazeNormalsMin: '0.0x (Flat)',
          hazeNormalsDef: '1.00x (Default)',
          hazeNormalsMax: '2.50x (Relief)',
          creviceShadow: 'Crevice Shadows: Contrast',
          creviceShadowTip: 'Crevice Shadows: Unclamps artificial ambient floor and deepens cavity self-shadowing between billow folds, boosting dynamic range to >8:1. (0.0x = washed-out grey fog, 1.0x = deep crevice contrast).',
          creviceShadowMin: '0.0x (Bright)',
          creviceShadowDef: '0.10x (Default)',
          creviceShadowMax: '2.50x (Deep)',
          coreOpacity: 'Core Opacity: S-Curve',
          coreOpacityTip: 'Core Opacity: Thermodynamic condensation phase transition. Eliminates see-through background in the core plume, rendering an opaque solid white cloud. (0.0x = translucent fog, 1.0x = opaque core).',
          coreOpacityMin: '0.0x (Translucent)',
          coreOpacityDef: '1.00x (Default)',
          coreOpacityMax: '3.00x (Solid)',
          vorticityDetail: 'Micro-Vorticity: Fold Texture',
          vorticityDetailTip: 'Micro-Vorticity: Adds high-frequency shear micro-ripples along plume boundaries to eliminate smooth trilinear voxel smear. (0.0x = smooth, 1.0x = cauliflower florets).',
          vorticityDetailMin: '0.0x (Smooth)',
          vorticityDetailDef: '1.00x (Default)',
          vorticityDetailMax: '2.50x (Floret)',
          sectionTrail: 'Plume Dynamics & Lifetime',
          coreLifetime: 'Core Plume Lifetime',
          coreLifetimeTip: 'Core Plume Lifetime: Slows dissipation of dense smoke core (4-6s), extending visible smoke trail behind vehicle by several car lengths.',
          coreLifeMin: '0.05x (Quick Fade)',
          coreLifeDef: '0.25x (Default)',
          coreLifeMax: '2.50x (Long Plume)',
          dispersionRate: 'Plume Dispersion Rate',
          dispersionRateTip: 'Dispersion Rate: Controls how quickly mature smoke fades away far behind the car without affecting tire-level density.',
          dispRateMin: '0.20x (Lingering)',
          dispRateDef: '0.40x (Default)',
          dispRateMax: '3.00x (Fast Fade)',
          underbodyEject: 'Underbody Ejection',
          underbodyEjectTip: 'Underbody Ejection: Force of the underbody air stream propelling smoke rearward through the diffuser during wheel slip.',
          underbodyEjectMin: '0.0x (Off)',
          underbodyEjectDef: '0.20x (Default)',
          underbodyEjectMax: '3.0x (High)',
          archEject: 'Wheel Arch Ejection',
          archEjectTip: 'Wheel Arch Ejection: Velocity of the downward air jet propelling smoke through wheel wells onto the asphalt.',
          archEjectMin: '0.0x (Off)',
          archEjectDef: '0.15x (Default)',
          archEjectMax: '3.00x (Max)',
          roadDamping: 'Road Braking',
          roadDampingTip: 'Road Braking: Viscous air deceleration in boundary layer (first 25 cm above road), preventing unnatural sliding of smoke base.',
          roadDampMin: '0.0x (Slick)',
          roadDampDef: '0.55x (Default)',
          roadDampMax: '5.0x (Sticky)',
          smokeDrag: 'Headwind Drag (Turbulent Braking)',
          smokeDragTip: 'Headwind Drag (Turbulent Braking): Global aerodynamic deceleration against standing ambient air outside the wake cavity, generating 3D shear turbulence and tumbling billows. Controls the aggressiveness of plume braking.',
          smokeDragMin: '0.0x (No Drag)',
          smokeDragDef: '0.15x (Default)',
          smokeDragMax: '3.0x (Fast Braking)',
          sectionSlipstream: '6. Slipstream Aerodynamic Pocket & 3D Turbulence',
          slipstream: 'Slipstream Hold Strength',
          slipstreamTip: 'Strength of smoke retention and forward entrainment inside the vehicle wake depression cavity (omnidirectional vector-based). Traps smoke in the slipstream cavity and gradually sheds it downstream.',
          slipstreamMin: '0.00x (No Slipstream)',
          slipstreamDef: '0.75x (Default)',
          slipstreamMax: '2.50x (Strong Hold)',
          slipstreamSpeedLimit: 'Smoke Hold Speed Limit',
          slipstreamSpeedLimitTip: 'Maximum relative speed difference between vehicle and smoke plume. Prevents smoke from falling behind faster than this limit (km/h), eliminating high-speed accordion gap.',
          slipstreamSpeedLimitMin: '30 km/h (Tight hold)',
          slipstreamSpeedLimitDef: '50 km/h (Default)',
          slipstreamSpeedLimitMax: '360 km/h (Free release)',
          slipstreamHoldTime: 'Smoke Hold Duration',
          slipstreamHoldTimeTip: 'Duration of smoke retention inside the wake pocket behind vehicle (in ms) before smooth release into ambient air.',
          slipstreamHoldTimeMin: '100 ms (Fast)',
          slipstreamHoldTimeDef: '200 ms (Default)',
          slipstreamHoldTimeMax: '2000 ms (Long pocket)',
          slipstreamBezier: 'Hold Release S-Curve (Bézier)',
          slipstreamBezierTip: 'Aerodynamic Base Wake Cavity: determines the release profile of smoke trapped behind the moving vehicle. X-axis is hold progress (0%..100%). Y-axis is smoke velocity retention (100%..0%). P1 shapes detachment softness at bumper, P2 shapes smooth transition into ambient air.',
          bezierAxisSlipTime: 'Hold Progress (time)',
          bezierAxisSlipHold: 'Wake Retention (%)',
          bezierPresetSmooth: 'Smooth S',
          bezierPresetProgressive: 'Progressive',
          bezierPresetAggressive: 'Aggressive',
          bezierPresetLingering: 'Lingering',
          bezierPresetFast: 'Fast Release',
          bezierPresetLinear: 'Linear',
          slipstreamTurbScale: '3D Curl Vortex Scale',
          slipstreamTurbScaleTip: 'Spatial eddy size of divergence-free 3D curl noise inside the slipstream cavity. Smaller = tight swirling ripples, larger = wide billowing vortex masses.',
          slipstreamTurbScaleMin: '0.20x (Fine Eddies)',
          slipstreamTurbScaleDef: '0.30x (Default)',
          slipstreamTurbScaleMax: '3.00x (Large Billows)',
          slipstreamTurbStrength: '3D Curl Turbulence Strength',
          slipstreamTurbStrengthTip: 'Intensity of rotational 3D curl churn inside the depression pocket. Blends smoke from both wheels together smoothly without head-on collisions or upward updrafts.',
          slipstreamTurbStrengthMin: '0.00x (Off)',
          slipstreamTurbStrengthDef: '0.50x (Default)',
          slipstreamTurbStrengthMax: '3.00x (Vigorous Churn)',
          debugWakeModeTitle: '3D Wake Cavity Visualizer (Debug)',
          debugWakeModeTip: 'Renders the 3D wake cavity boundary (translucent turquoise iso-volume with Fresnel rim) and dynamic flow vectors (upward recirculation behind bumper, inward suction, and trailing wake). Enables live calibration of cavity geometry across all vehicles.',
          wakeModeOff: 'Normal Smoke',
          wakeModeBubble: '3D Bubble',
          wakeModeFlow: 'Bubble + Currents',
          thermalBuoyancy: 'Thermal Buoyancy',
          thermalBuoyancyTip: 'Thermal Buoyancy: Convective Archimedean lift of hot smoke. Lower it (e.g. 0.2x-0.5x) to keep smoke trailing low across the asphalt instead of floating skyward.',
          thermalBuoyMin: '0.0x (Flat Ground)',
          thermalBuoyDef: '0.10x (Default)',
          thermalBuoyMax: '1.0x (Skyward)',
          sectionGrid: '7. Rendering & GPU Voxel Grid',
          raymarchQuality: 'Raymarch Quality',
          qualityMin: '1.0x (Fast)',
          qualityBal: '2.0x (Nyquist / Sharp)',
          qualityMax: '5.0x (Max)',
          voxelSize: 'Voxel Resolution',
          voxelMin: '40 mm (Ultra)',
          voxelDrift: '64 mm (Drift)',
          voxelMax: '100 mm (Fast)',
          domainSize: 'Horizontal Box Size',
          domainSizeTip: 'Horizontal Box Size: Physical extent of the simulation domain along X and Y axes (from 6.0 to 70.0 m). Expands simulation area without altering voxel resolution (grid dimensions scale proportionally).',
          domainMin: '6.0 m',
          domainDef: '13.5 m (Default)',
          domainMax: '70.0 m',
          toggleHint: 'Menu key: Insert / F7',
          navierStokes: 'Navier-Stokes',
          presetDefault: 'Default',
          presetTitle: 'Tuning Presets',
          presetSlots: 'Slots',
          presetLimitNotice: 'Preset limit reached (10/10).',
          presetSandboxNotice: 'Sandbox mode: Preset limit (10/10) reached. Settings are active in-game, but will not be saved automatically until you select or free a preset slot.',
          presetAddBtn: 'Add Preset (+)',
          presetDuplicateBtn: 'Duplicate Preset (❐)',
          presetDeleteBtn: 'Delete Preset',
          presetRenameBtn: 'Rename Preset',
          presetDuplicateWord: 'Duplicate',
          presetAddWord: 'Create',
          presetRenameWord: 'Rename',
          presetDeleteWord: 'Delete',
          resetWord: 'Reset',
          resetSectionTip: 'Reset parameters in this section to factory defaults',
          presetLimitReached: 'Limit (10/10)',
          presetNamePlaceholder: 'Preset name',
          slipstreamBetaTitle: 'Experimental Feature (BETA)',
          slipstreamBetaDesc: 'Wake cavity physics is in early calibration and may behave roughly. Wake retention and vortex dynamics will be significantly refined in upcoming updates.',
          gpuLoadWarn: 'High GPU Load: Grid volume is ',
          gpuLoadWarnSuffix: 'M voxels (> 5M). May reduce FPS.',
        }
      };

      // Language support with localStorage persistence
      let initialLang = 'ru';
      try {
        const stored = localStorage.getItem('realSmoke3D_lang');
        if (stored === 'ru' || stored === 'en') initialLang = stored;
      } catch (e) {}
      $scope.lang = initialLang;

      $scope.toggleLang = function () {
        $scope.lang = ($scope.lang === 'ru') ? 'en' : 'ru';
        try {
          localStorage.setItem('realSmoke3D_lang', $scope.lang);
        } catch (e) {}
        if (typeof $scope.fitHostContainer === 'function') $scope.fitHostContainer();
      };

      $scope.t = function (key) {
        if (i18n[$scope.lang] && i18n[$scope.lang][key] !== undefined) {
          return i18n[$scope.lang][key];
        }
        if (i18n.ru && i18n.ru[key] !== undefined) {
          return i18n.ru[key];
        }
        return key;
      };

      $scope.isCollapsed = false;
      try {
        const storedCollapse = localStorage.getItem('realSmoke3D_collapsed');
        if (storedCollapse !== null) $scope.isCollapsed = (storedCollapse === 'true');
      } catch (e) {}

      // Collapsible accordion sections
      $scope.sections = {
        telemetry: true,
        optics: true,
        equity: true,
        wheel: false,
        turb: false,
        trail: false,
        slipstream: true,
        grid: false
      };
      try {
        const storedSections = localStorage.getItem('realSmoke3D_sections');
        if (storedSections) {
          const parsed = JSON.parse(storedSections);
          if (parsed && typeof parsed === 'object') {
            Object.assign($scope.sections, parsed);
          }
        }
      } catch (e) {}

      $scope.toggleSection = function (id) {
        $scope.sections[id] = !$scope.sections[id];
        try {
          localStorage.setItem('realSmoke3D_sections', JSON.stringify($scope.sections));
        } catch (e) {}
        if (typeof $scope.fitHostContainer === 'function') $scope.fitHostContainer();
      };

      $scope.diagStatus = 'CONNECTING';
      $scope.diagCode = 'CONNECTING';
      $scope.diagApi = 'D3D11';
      $scope.diagApiLabel = 'D3D11';
      $scope.diagScaled = false;
      $scope.diagScalePct = 100;
      $scope.diagDepthW = 0;
      $scope.diagDepthH = 0;
      $scope.diagFrameW = 0;
      $scope.diagFrameH = 0;
      $scope.diagHdr = false;
      $scope.diagUiCaptured = true;
      $scope.conflictingAddon = null;
      $scope.diagFrames = 0;
      $scope.particleConflict = false;
      $scope.particleConflictMod = null;

      $scope.getDiagTooltip = function () {
        if ($scope.diagStatus === 'FAULT') {
          return ($scope.t('diagEngineFault') || 'Fault') + ': ' + $scope.diagCode;
        }
        if ($scope.diagStatus !== 'OK') {
          return $scope.t('diagEngineConnecting') || 'Connecting...';
        }
        var isRu = ($scope.lang === 'ru');
        var res = '';
        if ($scope.diagDepthW && $scope.diagFrameW) {
          res = ' | 3D: ' + $scope.diagDepthW + 'x' + $scope.diagDepthH + ' \u2192 ' + $scope.diagFrameW + 'x' + $scope.diagFrameH;
          if ($scope.diagScaled && $scope.diagScalePct < 100) {
            res += ' (' + $scope.diagScalePct + '%)';
          }
        }
        var hdrStr = $scope.diagHdr ? ' | HDR10' : '';
        var uiStr = ' | UI: ' + ($scope.diagUiCaptured ? (isRu ? 'Синхрон' : 'Synced') : (isRu ? 'Рассинхрон' : 'Desynced'));
        return ($scope.diagApiLabel || $scope.diagApi || 'D3D11') + res + hdrStr + uiStr;
      };
      $scope.particleSuppressed = true;
      $scope.showDiagDetails = true;
      $scope.toggleDiagDetails = function () {
        $scope.showDiagDetails = !$scope.showDiagDetails;
        if (typeof $scope.fitHostContainer === 'function') $scope.fitHostContainer();
      };

      $scope.$evalAsync(function () {
        const verEl = ($element && $element[0]) ? $element[0].querySelector('.rs-badge-ver') : document.querySelector('.rs-badge-ver');
        if (verEl && verEl.textContent.indexOf('0.8.12.9') === -1) {
          $scope.diagStatus = 'FAULT';
          $scope.diagCode = 'ERROR_VERSION_MISMATCH';
        }
      });

      $scope.flTemp = 20;
      $scope.frTemp = 20;
      $scope.rlTemp = 20;
      $scope.rrTemp = 20;

      $scope.flSlip = 0.0;
      $scope.frSlip = 0.0;
      $scope.rlSlip = 0.0;
      $scope.rrSlip = 0.0;

      $scope.totalEmission = 0.0;
      $scope.activeVoxels = 0;
      $scope.activeSmokeFraction = 0.0;
      $scope.simulationQuality = 2.0;
      $scope.pendingQuality = null;
      $scope.voxelMillimeters = 64;
      $scope.domainSize = 13.5;
      $scope.gridWidth = 216;
      $scope.gridHeight = 216;
      $scope.gridDepth = 60;
      $scope.domainX = 13.5;
      $scope.domainY = 13.5;
      $scope.domainZ = 3.84;

      // Burnout Equity parameters
      $scope.heatThreshold = 70;
      $scope.frictionSens = 0.35;
      $scope.frictionTime = 2.00;
      $scope.smokeOnset = 2.00;
      $scope.smokeDecay = 1.00;

      // Surface profile and Sand parameters
      $scope.activeSurfaceProfile = 'asphalt'; // 'asphalt' | 'sand'
      $scope.isSurfaceDropdownOpen = false;
      $scope.toggleSurfaceDropdown = function($event) {
        if ($event) $event.stopPropagation();
        $scope.isSurfaceDropdownOpen = !$scope.isSurfaceDropdownOpen;
      };
      $scope.closeSurfaceDropdown = function() {
        $scope.isSurfaceDropdownOpen = false;
      };
      $scope.selectSurfaceProfile = function(profile) {
        if (profile === 'asphalt' || profile === 'sand') {
          if ($scope.activeSurfaceProfile === 'asphalt' || $scope.activeSurfaceProfile === 'sand') {
            saveCurrentSurfaceFromScope($scope.activeSurfaceProfile);
          }
          $scope.activeSurfaceProfile = profile;
          physicsPendingUntil = Date.now() + PHYSICS_PENDING_MS;
          callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setPhysicsParam("activeSurfaceProfile", "' + profile + '")');
          loadSurfaceIntoScope(profile, true);
          onUserModifiedParam('activeSurfaceProfile', profile);
        }
        $scope.isSurfaceDropdownOpen = false;
        if (typeof $scope.fitHostContainer === 'function') {
          setTimeout($scope.fitHostContainer, 30);
        }
      };
      $scope.setSurfaceProfile = function(profile) {
        $scope.selectSurfaceProfile(profile);
      };
      $scope.onSurfaceProfileChange = function() {
        if (typeof $scope.fitHostContainer === 'function') {
          setTimeout($scope.fitHostContainer, 30);
        }
      };

      $scope.sandDustScale = 1.00;
      $scope.sandDustSens = 1.00;
      $scope.sandDustEnabled = true;
      $scope.asphaltSmokeEnabled = true;

      $scope.toggleSurfaceActivity = function(surface) {
        physicsPendingUntil = Date.now() + PHYSICS_PENDING_MS;
        if (surface === 'sand') {
          $scope.sandDustEnabled = !$scope.sandDustEnabled;
          callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setSandDustEnabled(' + ($scope.sandDustEnabled ? 'true' : 'false') + ')');
          onUserModifiedParam('sandDustEnabled', $scope.sandDustEnabled);
        } else if (surface === 'asphalt') {
          $scope.asphaltSmokeEnabled = !$scope.asphaltSmokeEnabled;
          callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setAsphaltSmokeEnabled(' + ($scope.asphaltSmokeEnabled ? 'true' : 'false') + ')');
          onUserModifiedParam('asphaltSmokeEnabled', $scope.asphaltSmokeEnabled);
        }
      };

      $scope.isCurrentSurfaceActive = function() {
        return ($scope.activeSurfaceProfile === 'sand') ? $scope.sandDustEnabled : $scope.asphaltSmokeEnabled;
      };

      $scope.toggleCurrentSurfaceActivity = function() {
        $scope.toggleSurfaceActivity($scope.activeSurfaceProfile);
      };

      // Effect Mute / Bypass for individual A/B testing
      $scope.paramEnabled = {};
      $scope.savedParamValues = {};

      const toggleableParams = [
        'heatThreshold', 'frictionSens', 'frictionTime', 'smokeOnset', 'smokeOnsetBezier', 'smokeDecay',
        'sandDustScale', 'sandDustSens',
        'hazeNormals', 'creviceShadow', 'coreOpacity', 'vorticityDetail',
        'treadSaturation', 'treadCoupling', 'edgeDispersion',
        'turbTransition', 'turbRelax', 'turbScale1', 'turbStrength1', 'turbScale2', 'turbStrength2', 'turbArch', 'turbArchScale',
        'coreLifetime', 'dispersionRate', 'underbodyEject',
        'archEject', 'roadDamping', 'smokeDrag', 'slipstream', 'slipstreamSpeedLimit', 'slipstreamHoldTime', 'slipstreamTurbScale', 'slipstreamTurbStrength', 'thermalBuoyancy'
      ];
      for (let i = 0; i < toggleableParams.length; i++) {
        $scope.paramEnabled[toggleableParams[i]] = true;
      }

      $scope.isParamEnabled = function (param) {
        return $scope.paramEnabled[param] !== false;
      };

      function sendPhysicsParamToLua(param, val) {
        if (param === 'simulationQuality') {
          callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setSimulationQuality(' + Number(val).toFixed(1) + ')');
        } else if (param === 'voxelMillimeters') {
          callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setVoxelSize(' + (Number(val) / 1000).toFixed(3) + ')');
        } else if (param === 'domainSize') {
          callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setDomainSize(' + Number(val).toFixed(2) + ')');
        } else if (param === 'smokeColor' || param === 'dustColor') {
          if (Array.isArray(val) && val.length >= 3) {
            callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setPhysicsParam("' + param + '", {' + Number(val[0]).toFixed(3) + ', ' + Number(val[1]).toFixed(3) + ', ' + Number(val[2]).toFixed(3) + '})');
          }
        } else if (param === 'smokeOnsetBezier') {
          if ($scope.syncSmokeOnsetBezierToLua) $scope.syncSmokeOnsetBezierToLua();
        } else if (param === 'smokeDecayBezier') {
          if ($scope.syncSmokeDecayBezierToLua) $scope.syncSmokeDecayBezierToLua();
        } else if (param === 'slipstreamBezier') {
          if ($scope.syncBezierToLua) $scope.syncBezierToLua();
        } else {
          callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setPhysicsParam("' + param + '", ' + Number(val).toFixed(2) + ')');
        }
      }

      $scope.toggleParam = function (param, offValue) {
        if ($scope.paramEnabled[param] === undefined) {
          $scope.paramEnabled[param] = true;
        }

        const effectiveOff = (offValue !== undefined) ? offValue : (PARAM_OFF_VALUES[param] !== undefined ? PARAM_OFF_VALUES[param] : 0.0);
        const activeProf = ($scope.activeSurfaceProfile === 'sand') ? 'sand' : 'asphalt';
        const isSurfaceShared = (SURFACE_SHARED_PARAMS.indexOf(param) !== -1);

        if ($scope.paramEnabled[param]) {
          $scope.savedParamValues[param] = deepClone($scope[param]);
          $scope.paramEnabled[param] = false;
          if (isSurfaceShared) {
            if (!$scope.surfaceParamEnabled[activeProf]) $scope.surfaceParamEnabled[activeProf] = {};
            if (!$scope.surfaceSavedParamValues[activeProf]) $scope.surfaceSavedParamValues[activeProf] = {};
            if (!$scope.surfaceParams[activeProf]) $scope.surfaceParams[activeProf] = {};
            $scope.surfaceParamEnabled[activeProf][param] = false;
            $scope.surfaceSavedParamValues[activeProf][param] = deepClone($scope.savedParamValues[param]);
            $scope.surfaceParams[activeProf][param] = deepClone($scope.savedParamValues[param]);
          }
          $scope[param] = effectiveOff;
          physicsPendingUntil = Date.now() + PHYSICS_PENDING_MS;
          sendPhysicsParamToLua(param, effectiveOff);
          if ($scope.activePresetId === 'default') {
            onUserModifiedParam(param, $scope.savedParamValues[param]);
          } else {
            savePresetsToStorage();
          }
        } else {
          $scope.paramEnabled[param] = true;
          let restoredVal = $scope.savedParamValues[param];
          if (restoredVal === undefined && isSurfaceShared && $scope.surfaceSavedParamValues[activeProf] && $scope.surfaceSavedParamValues[activeProf][param] !== undefined) {
            restoredVal = $scope.surfaceSavedParamValues[activeProf][param];
          }
          if (restoredVal === undefined && isSurfaceShared && $scope.surfaceParams[activeProf] && $scope.surfaceParams[activeProf][param] !== undefined) {
            restoredVal = $scope.surfaceParams[activeProf][param];
          }
          if (restoredVal === undefined) {
            if ($scope.activePresetId !== 'default') {
              const activeP = $scope.presets.find(function (p) { return p.id === $scope.activePresetId; });
              if (activeP && isSurfaceShared && activeP.surfaceParams && activeP.surfaceParams[activeProf] && activeP.surfaceParams[activeProf][param] !== undefined) {
                restoredVal = activeP.surfaceParams[activeProf][param];
              } else if (activeP && activeP.params && activeP.params[param] !== undefined) {
                restoredVal = activeP.params[param];
              }
            }
            if (restoredVal === undefined && FACTORY_DEFAULTS[param] !== undefined) {
              restoredVal = FACTORY_DEFAULTS[param];
            }
          }
          delete $scope.savedParamValues[param];
          if (isSurfaceShared) {
            if (!$scope.surfaceParamEnabled[activeProf]) $scope.surfaceParamEnabled[activeProf] = {};
            $scope.surfaceParamEnabled[activeProf][param] = true;
            if ($scope.surfaceSavedParamValues[activeProf]) {
              delete $scope.surfaceSavedParamValues[activeProf][param];
            }
          }
          if (restoredVal !== undefined) {
            $scope[param] = deepClone(restoredVal);
            if (isSurfaceShared) {
              if (!$scope.surfaceParams[activeProf]) $scope.surfaceParams[activeProf] = {};
              $scope.surfaceParams[activeProf][param] = deepClone(restoredVal);
            }
            physicsPendingUntil = Date.now() + PHYSICS_PENDING_MS;
            sendPhysicsParamToLua(param, restoredVal);
          }
          if ($scope.activePresetId === 'default') {
            onUserModifiedParam(param, $scope[param]);
          } else {
            savePresetsToStorage();
          }
        }
      };

      // Physics tuning parameters (user dialed-in drift setup)
      $scope.underbodyEject = 0.20;
      $scope.archEject = 0.15;
      $scope.vorticityStrength = 0.40;
      $scope.roadDamping = 0.55;
      $scope.smokeDrag = 0.15;
      $scope.slipstream = 0.75;
      $scope.slipstreamTurbScale = 0.30;
      $scope.slipstreamTurbStrength = 0.50;
      $scope.slipstreamSpeedLimit = 50;
      $scope.slipstreamHoldTime = 200;
      $scope.showBezierEditor = false;
      $scope.slipstreamBezier = { x1: 1.00, y1: 1.00, x2: 1.00, y2: 0.00 };
      $scope.activeBezierDrag = null;

      $scope.showSmokeOnsetBezierEditor = false;
      $scope.smokeOnsetBezier = { x0: 70, y0: 0.0, x1: 0.25, y1: 0.05, x2: 0.55, y2: 0.95, x3: 220, y3: 1.00 };
      $scope.activeSmokeOnsetBezierDrag = null;

      $scope.showDecayBezierEditor = false;
      $scope.smokeDecayBezier = { duration: 1.50, y0: 1.00, x1: 0.25, y1: 0.95, x2: 0.65, y2: 0.15 };
      $scope.activeDecayBezierDrag = null;
      $scope.debugWakeMode = 0;
      $scope.coreLifetime = 0.25;
      $scope.thermalBuoyancy = 0.10;
      $scope.treadSaturation = 1.00;
      $scope.treadCoupling = 0.50;
      $scope.edgeDispersion = 0.50;
      $scope.dispersionRate = 0.40;
      $scope.treadTurbulence = 2.00;
      $scope.turbTransition = 1.20;
      $scope.turbRelax = 2.00;
      $scope.turbScale1 = 1.05;
      $scope.turbStrength1 = 1.30;
      $scope.turbScale2 = 0.75;
      $scope.turbStrength2 = 1.00;
      $scope.turbArch = 2.00;
      $scope.turbArchScale = 0.25;
      $scope.microFiber = 1.0;
      $scope.fiberScale = 1.0;
      $scope.hazeNormals = 1.00;
      $scope.creviceShadow = 0.10;
      $scope.coreOpacity = 1.00;
      $scope.vorticityDetail = 1.00;
      $scope.smokeColor = [1.0, 1.0, 1.0];
      $scope.dustColor = [0.76, 0.65, 0.50];
      $scope.colorPickerTarget = "smokeColor";
      $scope.isColorPickerOpen = false;
      $scope.pickerR = 255;
      $scope.pickerG = 255;
      $scope.pickerB = 255;
      $scope.pickerHex = '#FFFFFF';
      $scope.pickerPointerX = 0;
      $scope.pickerPointerY = 0;
      $scope.showPointer = false;
      $scope.initialColor = [1.0, 1.0, 1.0];

      const QUALITY_MIN = 0.1;
      const QUALITY_MAX = 5.0;
      const QUALITY_STEP = 0.1;
      const QUALITY_PENDING_MS = 800;
      let qualityPendingUntil = 0;

      const VOXEL_MIN_MM = 40;
      const VOXEL_MAX_MM = 100;
      const VOXEL_PENDING_MS = 800;
      let voxelPendingUntil = 0;

      const DOMAIN_MIN_M = 6.0;
      const DOMAIN_MAX_M = 70.0;
      const DOMAIN_PENDING_MS = 800;
      let domainPendingUntil = 0;

      const PHYSICS_PENDING_MS = 800;
      let physicsPendingUntil = 0;

      function numOr(val, def) {
        const n = Number(val);
        return Number.isFinite(n) ? n : def;
      }

      // ======================================================================
      // Authoritative Tuning Constants & Preset Schema
      // ======================================================================
      const PARAM_DEFINITIONS = {
        // Grid & Domain
        simulationQuality: { min: 1.0, max: 5.0, step: 0.1, default: 2.0, section: 'grid', unit: 'x' },
        voxelMillimeters: { min: 40, max: 100, step: 1, default: 64, section: 'grid', unit: 'mm' },
        domainSize: { min: 6.0, max: 70.0, step: 0.5, default: 13.5, section: 'grid', unit: 'm' },

        // Optics / Shading
        smokeColor: { type: 'color', default: [1.0, 1.0, 1.0], section: 'optics', surface: 'asphalt' },
        hazeNormals: { min: 0.0, max: 3.0, step: 0.05, default: 1.00, section: 'optics', unit: 'x' },
        creviceShadow: { min: 0.0, max: 3.0, step: 0.05, default: 0.10, section: 'optics', unit: 'x' },
        coreOpacity: { min: 0.0, max: 4.0, step: 0.05, default: 1.00, section: 'optics', unit: 'x' },
        vorticityDetail: { min: 0.0, max: 3.0, step: 0.05, default: 1.00, section: 'optics', unit: 'x' },

        // Burnout Equity & Friction & Thermal (Asphalt & Sand Surface Profiles)
        dustColor: { type: 'color', default: [0.76, 0.65, 0.50], section: 'equity', surface: 'sand' },
        heatThreshold: { min: 40.0, max: 120.0, step: 1.0, default: 70.0, section: 'equity', unit: '°C', surface: 'asphalt' },
        frictionSens: { min: 0.05, max: 3.0, step: 0.05, default: 0.35, section: 'equity', unit: 'x', surface: 'asphalt' },
        frictionTime: { min: 0.0, max: 3.0, step: 0.05, default: 2.00, section: 'equity', unit: 's', surface: 'asphalt' },
        smokeOnset: { min: 0.05, max: 3.0, step: 0.05, default: 2.00, section: 'equity', unit: 'x', surface: 'asphalt' },
        smokeOnsetBezier: { type: 'bezier', default: { x0: 70, y0: 0.0, x1: 0.25, y1: 0.05, x2: 0.55, y2: 0.95, x3: 220, y3: 1.00 }, section: 'equity', surface: 'asphalt' },
        smokeDecay: { min: 0.0, max: 5.0, step: 0.05, default: 1.50, section: 'equity', unit: 'x', surface: 'asphalt' },
        smokeDecayBezier: { type: 'bezier', default: { duration: 1.50, y0: 1.00, x1: 0.25, y1: 0.95, x2: 0.65, y2: 0.15 }, section: 'equity', surface: 'asphalt' },
        sandDustScale: { min: 0.0, max: 3.0, step: 0.05, default: 1.00, section: 'equity', unit: 'x', surface: 'sand' },
        sandDustSens: { min: 0.05, max: 3.0, step: 0.05, default: 1.00, section: 'equity', unit: 'x', surface: 'sand' },
        asphaltSmokeEnabled: { default: true, section: 'equity', isBoolean: true, surface: 'asphalt' },
        sandDustEnabled: { default: true, section: 'equity', isBoolean: true, surface: 'sand' },
        activeSurfaceProfile: { default: 'asphalt', section: 'equity', isString: true },

        // Wheel Dynamics
        treadSaturation: { min: 0.1, max: 7.0, step: 0.1, default: 1.00, section: 'wheel', unit: 'x' },
        treadCoupling: { min: 0.05, max: 1.00, step: 0.01, default: 0.50, section: 'wheel', unit: 'x' },
        edgeDispersion: { min: 0.05, max: 2.50, step: 0.05, default: 0.50, section: 'wheel', unit: 'x' },

        // Trail & Aerodynamics
        coreLifetime: { min: 0.05, max: 2.5, step: 0.05, default: 0.25, section: 'trail', unit: 's' },
        dispersionRate: { min: 0.1, max: 3.0, step: 0.05, default: 0.40, section: 'trail', unit: 'x' },
        underbodyEject: { min: 0.0, max: 3.0, step: 0.05, default: 0.20, section: 'trail', unit: 'x' },
        archEject: { min: 0.0, max: 3.0, step: 0.05, default: 0.15, section: 'trail', unit: 'x' },
        roadDamping: { min: 0.0, max: 5.0, step: 0.05, default: 0.55, section: 'trail', unit: 'x' },
        smokeDrag: { min: 0.0, max: 5.0, step: 0.05, default: 0.15, section: 'trail', unit: 'x' },
        thermalBuoyancy: { min: 0.0, max: 2.5, step: 0.05, default: 0.10, section: 'trail', unit: 'x' },

        // Turbulence
        turbTransition: { min: 0.0, max: 12.0, step: 0.1, default: 1.20, section: 'turb', unit: 'm' },
        turbRelax: { min: 0.2, max: 20.0, step: 0.1, default: 2.00, section: 'turb', unit: 's' },
        turbScale1: { min: 0.2, max: 3.0, step: 0.05, default: 1.05, section: 'turb', unit: 'x' },
        turbStrength1: { min: 0.0, max: 3.0, step: 0.05, default: 1.30, section: 'turb', unit: 'x' },
        turbScale2: { min: 0.2, max: 3.0, step: 0.05, default: 0.75, section: 'turb', unit: 'x' },
        turbStrength2: { min: 0.0, max: 3.0, step: 0.05, default: 1.00, section: 'turb', unit: 'x' },
        turbArch: { min: 0.0, max: 8.0, step: 0.1, default: 2.00, section: 'turb', unit: 'x' },
        turbArchScale: { min: 0.2, max: 3.0, step: 0.05, default: 0.25, section: 'turb', unit: 'x' },
        microFiber: { min: 0.0, max: 3.0, step: 0.05, default: 1.00, section: 'turb', unit: 'x' },
        fiberScale: { min: 0.2, max: 3.0, step: 0.05, default: 1.00, section: 'turb', unit: 'x' },

        // Slipstream
        slipstream: { min: 0.0, max: 5.0, step: 0.05, default: 0.75, section: 'slipstream', unit: 'x' },
        slipstreamSpeedLimit: { min: 5.0, max: 300.0, step: 5.0, default: 50.0, section: 'slipstream', unit: 'km/h' },
        slipstreamHoldTime: { min: 0.0, max: 2000.0, step: 10.0, default: 200.0, section: 'slipstream', unit: 'ms' },
        slipstreamBezier: { type: 'bezier', default: { x1: 1.00, y1: 1.00, x2: 1.00, y2: 0.00 }, section: 'slipstream' },
        slipstreamTurbScale: { min: 0.10, max: 5.0, step: 0.05, default: 0.30, section: 'slipstream', unit: 'x' },
        slipstreamTurbStrength: { min: 0.0, max: 5.0, step: 0.05, default: 0.50, section: 'slipstream', unit: 'x' }
      };

      const PARAM_OFF_VALUES = {
        heatThreshold: 120.0,
        frictionSens: 0.05,
        frictionTime: 0.0,
        smokeOnset: 3.0,
        smokeOnsetBezier: { x0: 120, y0: 0.0, x1: 0.25, y1: 0.05, x2: 0.55, y2: 0.95, x3: 220, y3: 1.00 },
        smokeDecay: 0.0,
        sandDustScale: 0.0,
        sandDustSens: 3.0,
        hazeNormals: 0.0,
        creviceShadow: 0.0,
        coreOpacity: 0.0,
        vorticityDetail: 0.0,
        treadSaturation: 0.1,
        treadCoupling: 0.05,
        edgeDispersion: 0.05,
        turbTransition: 0.0,
        turbRelax: 20.0,
        turbScale1: 0.2,
        turbStrength1: 0.0,
        turbScale2: 0.2,
        turbStrength2: 0.0,
        turbArch: 0.0,
        turbArchScale: 0.2,
        coreLifetime: 0.05,
        dispersionRate: 0.1,
        underbodyEject: 0.0,
        archEject: 0.0,
        roadDamping: 0.0,
        smokeDrag: 0.0,
        slipstream: 0.0,
        slipstreamSpeedLimit: 5.0,
        slipstreamHoldTime: 0.0,
        slipstreamTurbScale: 0.1,
        slipstreamTurbStrength: 0.0,
        thermalBuoyancy: 0.0
      };

      const PRESET_PARAM_KEYS = Object.keys(PARAM_DEFINITIONS);

      // Parameters shared by UI controls in Wheel, Optics, Turbulence, and Plume/Trail sections
      // that must be saved and restored independently per surface profile ('asphalt' vs 'sand').
      // Excluded per design: 'slipstream' (Section 6) and 'grid' (Section 7).
      const SURFACE_SHARED_PARAMS = [
        'treadSaturation', 'treadCoupling', 'edgeDispersion',
        'hazeNormals', 'creviceShadow', 'coreOpacity', 'vorticityDetail',
        'turbTransition', 'turbRelax', 'turbScale1', 'turbStrength1', 'turbScale2', 'turbStrength2', 'turbArch', 'turbArchScale', 'microFiber', 'fiberScale',
        'coreLifetime', 'dispersionRate', 'underbodyEject', 'archEject', 'roadDamping', 'smokeDrag', 'thermalBuoyancy'
      ];

      const FACTORY_DEFAULTS = {};
      for (const [key, def] of Object.entries(PARAM_DEFINITIONS)) {
        if (typeof def.default === 'object' && def.default !== null) {
          FACTORY_DEFAULTS[key] = Array.isArray(def.default) ? def.default.slice() : Object.assign({}, def.default);
        } else {
          FACTORY_DEFAULTS[key] = def.default;
        }
      }

      // Voxel grid load calculation according to native C++ CalculateGrid formula
      function alignUp(val, align) {
        return Math.ceil(val / align) * align;
      }

      $scope.getEstimatedGridVoxels = function () {
        const vM = ($scope.voxelMillimeters || 64) / 1000.0;
        const dM = $scope.domainSize || 13.5;
        const w = alignUp(Math.floor(dM / vM + 0.999), 8);
        const h = w;
        const d = alignUp(Math.floor(3.84 / vM + 0.999), 4);
        return w * h * d;
      };

      $scope.isHighVoxelLoad = function () {
        return $scope.getEstimatedGridVoxels() > 5000000;
      };

      // User Presets System (up to 10 user presets, immutable factory Default)
      $scope.presets = [];
      $scope.activePresetId = 'default';
      $scope.isPresetDropdownOpen = false;
      $scope.editingPresetId = null;
      $scope.showSandboxNotice = false;
      let sandboxNoticeTimeout = null;

      try {
        const storedPresets = localStorage.getItem('realSmoke3D_presets');
        if (storedPresets) {
          const parsed = JSON.parse(storedPresets);
          if (Array.isArray(parsed)) {
            $scope.presets = parsed.slice(0, 10);
          }
        }
        const storedActive = localStorage.getItem('realSmoke3D_activePresetId');
        if (storedActive) {
          if (storedActive === 'default' || $scope.presets.some(function (p) { return p.id === storedActive; })) {
            $scope.activePresetId = storedActive;
          }
        }
      } catch (e) {}

      function deepClone(obj) {
        if (obj === null || typeof obj !== 'object') return obj;
        if (Array.isArray(obj)) return obj.map(deepClone);
        const copy = {};
        for (const k in obj) {
          if (Object.prototype.hasOwnProperty.call(obj, k)) {
            copy[k] = deepClone(obj[k]);
          }
        }
        return copy;
      }

      // Per-surface isolated parameter state ('asphalt' vs 'sand')
      $scope.surfaceParams = { asphalt: {}, sand: {} };
      $scope.surfaceParamEnabled = { asphalt: {}, sand: {} };
      $scope.surfaceSavedParamValues = { asphalt: {}, sand: {} };

      function resetSurfaceMapsToFactory() {
        $scope.surfaceParams = { asphalt: {}, sand: {} };
        $scope.surfaceParamEnabled = { asphalt: {}, sand: {} };
        $scope.surfaceSavedParamValues = { asphalt: {}, sand: {} };
        for (let i = 0; i < SURFACE_SHARED_PARAMS.length; i++) {
          const k = SURFACE_SHARED_PARAMS[i];
          $scope.surfaceParams.asphalt[k] = deepClone(FACTORY_DEFAULTS[k]);
          $scope.surfaceParams.sand[k] = deepClone(FACTORY_DEFAULTS[k]);
          $scope.surfaceParamEnabled.asphalt[k] = true;
          $scope.surfaceParamEnabled.sand[k] = true;
        }
      }
      resetSurfaceMapsToFactory();

      function saveCurrentSurfaceFromScope(prof) {
        const targetProf = (prof === 'sand') ? 'sand' : 'asphalt';
        if (!$scope.surfaceParams[targetProf]) $scope.surfaceParams[targetProf] = {};
        if (!$scope.surfaceParamEnabled[targetProf]) $scope.surfaceParamEnabled[targetProf] = {};
        if (!$scope.surfaceSavedParamValues[targetProf]) $scope.surfaceSavedParamValues[targetProf] = {};
        for (let i = 0; i < SURFACE_SHARED_PARAMS.length; i++) {
          const k = SURFACE_SHARED_PARAMS[i];
          const isEn = ($scope.paramEnabled && $scope.paramEnabled[k] !== false);
          $scope.surfaceParamEnabled[targetProf][k] = isEn;
          if (!isEn && $scope.savedParamValues && $scope.savedParamValues[k] !== undefined) {
            $scope.surfaceSavedParamValues[targetProf][k] = deepClone($scope.savedParamValues[k]);
            $scope.surfaceParams[targetProf][k] = deepClone($scope.savedParamValues[k]);
          } else {
            delete $scope.surfaceSavedParamValues[targetProf][k];
            if ($scope[k] !== undefined) {
              $scope.surfaceParams[targetProf][k] = deepClone($scope[k]);
            } else if (FACTORY_DEFAULTS[k] !== undefined) {
              $scope.surfaceParams[targetProf][k] = deepClone(FACTORY_DEFAULTS[k]);
            }
          }
        }
      }

      function loadSurfaceIntoScope(prof, syncToLua) {
        const targetProf = (prof === 'sand') ? 'sand' : 'asphalt';
        const pMap = ($scope.surfaceParams && $scope.surfaceParams[targetProf]) ? $scope.surfaceParams[targetProf] : {};
        const enMap = ($scope.surfaceParamEnabled && $scope.surfaceParamEnabled[targetProf]) ? $scope.surfaceParamEnabled[targetProf] : {};
        const svMap = ($scope.surfaceSavedParamValues && $scope.surfaceSavedParamValues[targetProf]) ? $scope.surfaceSavedParamValues[targetProf] : {};

        for (let i = 0; i < SURFACE_SHARED_PARAMS.length; i++) {
          const k = SURFACE_SHARED_PARAMS[i];
          const baseVal = (pMap[k] !== undefined) ? pMap[k] : FACTORY_DEFAULTS[k];
          const isEn = (enMap[k] !== false);
          $scope.paramEnabled[k] = isEn;
          if (!isEn) {
            const savedVal = (svMap[k] !== undefined) ? svMap[k] : baseVal;
            $scope.savedParamValues[k] = deepClone(savedVal);
            const offVal = (PARAM_OFF_VALUES[k] !== undefined) ? PARAM_OFF_VALUES[k] : 0.0;
            $scope[k] = offVal;
            if (syncToLua) {
              sendPhysicsParamToLua(k, offVal);
            }
          } else {
            delete $scope.savedParamValues[k];
            $scope[k] = deepClone(baseVal);
            if (syncToLua) {
              sendPhysicsParamToLua(k, baseVal);
            }
          }
        }
      }

      function buildEffectiveSurfaceParamsForLua() {
        const out = { asphalt: {}, sand: {} };
        const profiles = ['asphalt', 'sand'];
        for (let pIdx = 0; pIdx < profiles.length; pIdx++) {
          const prof = profiles[pIdx];
          const pMap = ($scope.surfaceParams && $scope.surfaceParams[prof]) ? $scope.surfaceParams[prof] : {};
          const enMap = ($scope.surfaceParamEnabled && $scope.surfaceParamEnabled[prof]) ? $scope.surfaceParamEnabled[prof] : {};
          for (let i = 0; i < SURFACE_SHARED_PARAMS.length; i++) {
            const k = SURFACE_SHARED_PARAMS[i];
            const baseVal = (pMap[k] !== undefined) ? pMap[k] : FACTORY_DEFAULTS[k];
            if (enMap[k] === false) {
              out[prof][k] = (PARAM_OFF_VALUES[k] !== undefined) ? PARAM_OFF_VALUES[k] : 0.0;
            } else {
              out[prof][k] = deepClone(baseVal);
            }
          }
        }
        return out;
      }

      function snapshotCurrentScopeParams() {
        saveCurrentSurfaceFromScope($scope.activeSurfaceProfile);
        const snap = {};
        for (let i = 0; i < PRESET_PARAM_KEYS.length; i++) {
          const k = PRESET_PARAM_KEYS[i];
          if ($scope.paramEnabled && $scope.paramEnabled[k] === false && $scope.savedParamValues && $scope.savedParamValues[k] !== undefined) {
            snap[k] = deepClone($scope.savedParamValues[k]);
          } else if ($scope[k] !== undefined) {
            snap[k] = deepClone($scope[k]);
          } else if (FACTORY_DEFAULTS[k] !== undefined) {
            snap[k] = deepClone(FACTORY_DEFAULTS[k]);
          }
        }
        return snap;
      }

      function persistCurrentPresetSnapshot() {
        saveCurrentSurfaceFromScope($scope.activeSurfaceProfile);
        if ($scope.activePresetId && $scope.activePresetId !== 'default') {
          const curP = $scope.presets.find(function (p) { return p.id === $scope.activePresetId; });
          if (curP) {
            curP.params = snapshotCurrentScopeParams();
            if ($scope.paramEnabled) {
              curP.paramEnabled = Object.assign({}, $scope.paramEnabled);
            }
            if ($scope.savedParamValues) {
              curP.savedParamValues = deepClone($scope.savedParamValues);
            }
            curP.surfaceParams = deepClone($scope.surfaceParams);
            curP.surfaceParamEnabled = deepClone($scope.surfaceParamEnabled);
            curP.surfaceSavedParamValues = deepClone($scope.surfaceSavedParamValues);
          }
        }
      }

      function savePresetsToStorage() {
        try {
          persistCurrentPresetSnapshot();
          localStorage.setItem('realSmoke3D_presets', JSON.stringify($scope.presets));
          localStorage.setItem('realSmoke3D_activePresetId', $scope.activePresetId);
          // Dual-layer sync: persist state to GE Lua disk storage (survives CEF cache purges)
          const syncPayload = {
            presets: $scope.presets,
            activePresetId: $scope.activePresetId,
            lang: $scope.lang
          };
          const jsonArg = JSON.stringify(JSON.stringify(syncPayload));
          callLua('if syncRealSmokeUiStateToLua then syncRealSmokeUiStateToLua(' + jsonArg + ') end');
        } catch (e) {}
      }

      function getNextPresetName(basePrefix) {
        const prefix = basePrefix || 'Preset';
        let n = 1;
        while (true) {
          const candidate = prefix + ' ' + n;
          const exists = $scope.presets.some(function (p) {
            return p.name && p.name.toLowerCase() === candidate.toLowerCase();
          });
          if (!exists) return candidate;
          n++;
        }
      }

      function getDuplicatePresetName(originalName) {
        const isRu = ($scope.lang === 'ru');
        let candidate = originalName + (isRu ? ' (Копия)' : ' (Copy)');
        let exists = $scope.presets.some(function (p) {
          return p.name && p.name.toLowerCase() === candidate.toLowerCase();
        });
        if (!exists) return candidate;
        let n = 2;
        while (true) {
          candidate = originalName + (isRu ? (' (Копия ' + n + ')') : (' (Copy ' + n + ')'));
          exists = $scope.presets.some(function (p) {
            return p.name && p.name.toLowerCase() === candidate.toLowerCase();
          });
          if (!exists) return candidate;
          n++;
        }
      }

      function applyPresetToScopeAndLua(params, paramEnabledMap, savedParamValuesMap, surfaceParamsMap, surfaceParamEnabledMap, surfaceSavedMap) {
        physicsPendingUntil = Date.now() + 2500;
        qualityPendingUntil = Date.now() + 2500;
        voxelPendingUntil = Date.now() + 2500;
        domainPendingUntil = Date.now() + 2500;

        if (surfaceParamsMap === undefined && params && params !== FACTORY_DEFAULTS && $scope.activePresetId !== 'default') {
          const activeP = $scope.presets.find(function (p) { return p.id === $scope.activePresetId; });
          if (activeP) {
            surfaceParamsMap = activeP.surfaceParams;
            surfaceParamEnabledMap = activeP.surfaceParamEnabled;
            surfaceSavedMap = activeP.surfaceSavedParamValues;
          }
        }

        for (let i = 0; i < PRESET_PARAM_KEYS.length; i++) {
          const k = PRESET_PARAM_KEYS[i];
          const val = (params && params[k] !== undefined) ? params[k] : FACTORY_DEFAULTS[k];
          if (val !== undefined) {
            $scope[k] = deepClone(val);
          }
        }

        $scope.savedParamValues = {};
        if (savedParamValuesMap && typeof savedParamValuesMap === 'object') {
          for (const spk in savedParamValuesMap) {
            if (savedParamValuesMap.hasOwnProperty(spk)) {
              $scope.savedParamValues[spk] = deepClone(savedParamValuesMap[spk]);
            }
          }
        }

        if (paramEnabledMap && typeof paramEnabledMap === 'object') {
          for (const pk in paramEnabledMap) {
            if (paramEnabledMap.hasOwnProperty(pk)) {
              $scope.paramEnabled[pk] = paramEnabledMap[pk];
              if (paramEnabledMap[pk] === false) {
                if ($scope.savedParamValues[pk] === undefined && params && params[pk] !== undefined) {
                  $scope.savedParamValues[pk] = deepClone(params[pk]);
                }
                const offVal = (PARAM_OFF_VALUES[pk] !== undefined) ? PARAM_OFF_VALUES[pk] : 0.0;
                $scope[pk] = offVal;
              }
            }
          }
        } else {
          for (let i = 0; i < toggleableParams.length; i++) {
            $scope.paramEnabled[toggleableParams[i]] = true;
          }
        }

        resetSurfaceMapsToFactory();
        const activeProf = ($scope.activeSurfaceProfile === 'sand') ? 'sand' : 'asphalt';
        if (params && params !== FACTORY_DEFAULTS) {
          for (let i = 0; i < SURFACE_SHARED_PARAMS.length; i++) {
            const k = SURFACE_SHARED_PARAMS[i];
            if (params[k] !== undefined) {
              $scope.surfaceParams[activeProf][k] = deepClone(params[k]);
            }
            if (paramEnabledMap && paramEnabledMap[k] !== undefined) {
              $scope.surfaceParamEnabled[activeProf][k] = (paramEnabledMap[k] !== false);
            }
            if (savedParamValuesMap && savedParamValuesMap[k] !== undefined) {
              $scope.surfaceSavedParamValues[activeProf][k] = deepClone(savedParamValuesMap[k]);
            }
          }
        }
        const profiles = ['asphalt', 'sand'];
        for (let pIdx = 0; pIdx < profiles.length; pIdx++) {
          const prof = profiles[pIdx];
          if (surfaceParamsMap && surfaceParamsMap[prof] && typeof surfaceParamsMap[prof] === 'object') {
            for (let i = 0; i < SURFACE_SHARED_PARAMS.length; i++) {
              const k = SURFACE_SHARED_PARAMS[i];
              if (surfaceParamsMap[prof][k] !== undefined) {
                $scope.surfaceParams[prof][k] = deepClone(surfaceParamsMap[prof][k]);
              }
            }
          }
          if (surfaceParamEnabledMap && surfaceParamEnabledMap[prof] && typeof surfaceParamEnabledMap[prof] === 'object') {
            for (let i = 0; i < SURFACE_SHARED_PARAMS.length; i++) {
              const k = SURFACE_SHARED_PARAMS[i];
              if (surfaceParamEnabledMap[prof][k] !== undefined) {
                $scope.surfaceParamEnabled[prof][k] = (surfaceParamEnabledMap[prof][k] !== false);
              }
            }
          }
          if (surfaceSavedMap && surfaceSavedMap[prof] && typeof surfaceSavedMap[prof] === 'object') {
            for (let i = 0; i < SURFACE_SHARED_PARAMS.length; i++) {
              const k = SURFACE_SHARED_PARAMS[i];
              if (surfaceSavedMap[prof][k] !== undefined) {
                $scope.surfaceSavedParamValues[prof][k] = deepClone(surfaceSavedMap[prof][k]);
              }
            }
          }
        }
        loadSurfaceIntoScope(activeProf, false);

        try {
          const fullParams = {};
          for (let i = 0; i < PRESET_PARAM_KEYS.length; i++) {
            const k = PRESET_PARAM_KEYS[i];
            fullParams[k] = $scope[k];
          }
          const presetPayload = {
            params: fullParams,
            paramEnabled: $scope.paramEnabled,
            surfaceParams: buildEffectiveSurfaceParamsForLua()
          };
          const jsonStr = JSON.stringify(presetPayload);
          const luaStrArg = JSON.stringify(jsonStr);
          callLua('if applyRealSmokePreset then applyRealSmokePreset(' + luaStrArg + ') elseif realSmoke3DGE then realSmoke3DGE.applyPreset(' + luaStrArg + ') end');
          if ($scope.syncSmokeOnsetBezierToLua) {
            $scope.syncSmokeOnsetBezierToLua();
          }
          if ($scope.syncSmokeDecayBezierToLua) {
            $scope.syncSmokeDecayBezierToLua();
          }
          if ($scope.syncBezierToLua) {
            $scope.syncBezierToLua();
          }
          callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setSandDustEnabled(' + ($scope.sandDustEnabled ? 'true' : 'false') + ')');
          callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setAsphaltSmokeEnabled(' + ($scope.asphaltSmokeEnabled ? 'true' : 'false') + ')');
          callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setPhysicsParam("activeSurfaceProfile", "' + ($scope.activeSurfaceProfile || 'asphalt') + '")');
        } catch (e) {
          for (const k in params) {
            if (params.hasOwnProperty(k)) {
              if (k === 'simulationQuality') {
                callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setSimulationQuality(' + Number(params[k]).toFixed(1) + ')');
              } else if (k === 'voxelMillimeters') {
                callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setVoxelSize(' + (Number(params[k]) / 1000).toFixed(3) + ')');
              } else if (k === 'domainSize') {
                callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setDomainSize(' + Number(params[k]).toFixed(2) + ')');
              } else if (k === 'smokeColor' || k === 'dustColor') {
                const c = params[k];
                if (Array.isArray(c) && c.length >= 3) {
                  callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setPhysicsParam("' + k + '", {' + Number(c[0]).toFixed(3) + ', ' + Number(c[1]).toFixed(3) + ', ' + Number(c[2]).toFixed(3) + '})');
                }
              } else {
                callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setPhysicsParam("' + k + '", ' + Number(params[k]).toFixed(2) + ')');
              }
            }
          }
        }
      }

      function onUserModifiedParam(paramKey, val) {
        saveCurrentSurfaceFromScope($scope.activeSurfaceProfile);
        if ($scope.activePresetId !== 'default') {
          const activeP = $scope.presets.find(function (p) { return p.id === $scope.activePresetId; });
          if (activeP) {
            if (!activeP.params) activeP.params = {};
            activeP.params[paramKey] = deepClone(val);
            if ($scope.paramEnabled) {
              activeP.paramEnabled = Object.assign({}, $scope.paramEnabled);
            }
            if ($scope.savedParamValues) {
              activeP.savedParamValues = deepClone($scope.savedParamValues);
            }
            activeP.surfaceParams = deepClone($scope.surfaceParams);
            activeP.surfaceParamEnabled = deepClone($scope.surfaceParamEnabled);
            activeP.surfaceSavedParamValues = deepClone($scope.surfaceSavedParamValues);
            savePresetsToStorage();
          }
        } else {
          // On default preset
          if ($scope.presets.length < 10) {
            // Auto-fork into a new preset
            const newId = 'preset_' + Date.now();
            const newName = getNextPresetName('Preset');
            const params = snapshotCurrentScopeParams();
            params[paramKey] = val;
            const enabledCopy = Object.assign({}, $scope.paramEnabled);
            const newPreset = {
              id: newId,
              name: newName,
              params: params,
              paramEnabled: enabledCopy,
              savedParamValues: deepClone($scope.savedParamValues),
              surfaceParams: deepClone($scope.surfaceParams),
              surfaceParamEnabled: deepClone($scope.surfaceParamEnabled),
              surfaceSavedParamValues: deepClone($scope.surfaceSavedParamValues)
            };
            $scope.presets.push(newPreset);
            $scope.activePresetId = newId;
            savePresetsToStorage();
          } else {
            // 10/10 limit reached: unhindered sandbox experimentation mode
            $scope.showSandboxNotice = true;
            if (sandboxNoticeTimeout) clearTimeout(sandboxNoticeTimeout);
            sandboxNoticeTimeout = setTimeout(function () {
              $scope.$evalAsync(function () {
                $scope.showSandboxNotice = false;
              });
            }, 6000);
          }
        }
      }

      $scope.getActivePresetName = function () {
        if ($scope.activePresetId === 'default') {
          return $scope.t('presetDefault');
        }
        const found = $scope.presets.find(function (p) { return p.id === $scope.activePresetId; });
        return found ? found.name : $scope.t('presetDefault');
      };

      $scope.togglePresetDropdown = function ($event) {
        if ($event) $event.stopPropagation();
        $scope.isPresetDropdownOpen = !$scope.isPresetDropdownOpen;
      };

      $scope.closePresetDropdown = function () {
        if ($scope.editingPresetId) {
          const ep = $scope.presets.find(function (p) { return p.id === $scope.editingPresetId; });
          if (ep) {
            $scope.finishRenaming(ep, ep.name);
          }
        }
        $scope.isPresetDropdownOpen = false;
        $scope.editingPresetId = null;
      };

      $scope.selectPreset = function (id) {
        persistCurrentPresetSnapshot();
        if (id === 'default') {
          $scope.activePresetId = 'default';
          applyPresetToScopeAndLua(FACTORY_DEFAULTS, null);
        } else {
          const found = $scope.presets.find(function (p) { return p.id === id; });
          if (found) {
            $scope.activePresetId = id;
            applyPresetToScopeAndLua(found.params, found.paramEnabled, found.savedParamValues, found.surfaceParams, found.surfaceParamEnabled, found.surfaceSavedParamValues);
          }
        }
        savePresetsToStorage();
        $scope.closePresetDropdown();
      };

      $scope.createPreset = function ($event) {
        if ($event) $event.stopPropagation();
        if ($scope.presets.length >= 10) return;

        persistCurrentPresetSnapshot();

        const newId = 'preset_' + Date.now();
        const newName = getNextPresetName('Preset');
        const currentParams = snapshotCurrentScopeParams();
        const enabledCopy = Object.assign({}, $scope.paramEnabled);

        const newPreset = {
          id: newId,
          name: newName,
          params: currentParams,
          paramEnabled: enabledCopy,
          savedParamValues: deepClone($scope.savedParamValues),
          surfaceParams: deepClone($scope.surfaceParams),
          surfaceParamEnabled: deepClone($scope.surfaceParamEnabled),
          surfaceSavedParamValues: deepClone($scope.surfaceSavedParamValues)
        };

        $scope.presets.push(newPreset);
        $scope.activePresetId = newId;
        savePresetsToStorage();
        $scope.startRenaming(newPreset.id, $event);
      };

      $scope.duplicatePreset = function ($event) {
        if ($event) $event.stopPropagation();
        if ($scope.presets.length >= 10) return;

        persistCurrentPresetSnapshot();

        const newId = 'preset_' + Date.now();
        let newName;
        if ($scope.activePresetId === 'default') {
          newName = getNextPresetName('Preset');
        } else {
          const activeP = $scope.presets.find(function (p) { return p.id === $scope.activePresetId; });
          newName = activeP ? getDuplicatePresetName(activeP.name) : getNextPresetName('Preset');
        }

        const currentParams = snapshotCurrentScopeParams();
        const enabledCopy = Object.assign({}, $scope.paramEnabled);

        const newPreset = {
          id: newId,
          name: newName,
          params: currentParams,
          paramEnabled: enabledCopy,
          savedParamValues: deepClone($scope.savedParamValues),
          surfaceParams: deepClone($scope.surfaceParams),
          surfaceParamEnabled: deepClone($scope.surfaceParamEnabled),
          surfaceSavedParamValues: deepClone($scope.surfaceSavedParamValues)
        };

        $scope.presets.push(newPreset);
        $scope.activePresetId = newId;
        savePresetsToStorage();
        $scope.startRenaming(newPreset.id, $event);
      };

      $scope.deletePreset = function (id, $event) {
        if ($event) $event.stopPropagation();
        if (id === 'default') return;

        const idx = $scope.presets.findIndex(function (p) { return p.id === id; });
        if (idx !== -1) {
          $scope.presets.splice(idx, 1);
          if ($scope.activePresetId === id) {
            $scope.selectPreset('default');
          } else {
            savePresetsToStorage();
          }
        }
      };

      $scope.startRenaming = function (id, $event) {
        if ($event) $event.stopPropagation();
        if (id === 'default') return;
        const p = $scope.presets.find(function (item) { return item.id === id; });
        if (!p) return;
        $scope.editingPresetId = id;
        $scope.$evalAsync(function () {
          try {
            const el = document.getElementById('rs-preset-input-' + id);
            if (el) {
              el.focus();
              if (typeof el.select === 'function') el.select();
            }
          } catch (e) {}
        });
      };

      $scope.onRenameKeydown = function ($event, p) {
        $event.stopPropagation();
        if ($event.keyCode === 13) {
          if ($event.target && typeof $event.target.blur === 'function') {
            $event.target.blur();
          }
          $scope.finishRenaming(p, p.name);
        } else if ($event.keyCode === 27) {
          if ($event.target && typeof $event.target.blur === 'function') {
            $event.target.blur();
          }
          $scope.editingPresetId = null;
        }
      };

      $scope.finishRenaming = function (preset, newName) {
        if ($scope.editingPresetId !== preset.id) return;
        try {
          const el = document.getElementById('rs-preset-input-' + preset.id);
          if (el && typeof el.blur === 'function') {
            el.blur();
          }
          if (document.activeElement && typeof document.activeElement.blur === 'function') {
            document.activeElement.blur();
          }
          if (typeof window.blur === 'function') {
            window.blur();
          }
        } catch (e) {}

        let trimmed = (newName !== undefined && newName !== null) ? String(newName).trim() : '';
        if (!trimmed) {
          trimmed = preset.name || getNextPresetName('Preset');
        }

        let finalName = trimmed;
        let conflict = $scope.presets.some(function (p) {
          return p.id !== preset.id && p.name && p.name.toLowerCase() === finalName.toLowerCase();
        });
        let n = 2;
        while (conflict) {
          finalName = trimmed + ' (' + n + ')';
          conflict = $scope.presets.some(function (p) {
            return p.id !== preset.id && p.name && p.name.toLowerCase() === finalName.toLowerCase();
          });
          n++;
        }

        preset.name = finalName;
        $scope.editingPresetId = null;
        savePresetsToStorage();
      };

      // Apply saved active preset configuration unconditionally on startup
      if ($scope.activePresetId !== 'default') {
        const savedActive = $scope.presets.find(function (p) { return p.id === $scope.activePresetId; });
        if (savedActive && savedActive.params) {
          applyPresetToScopeAndLua(savedActive.params, savedActive.paramEnabled, savedActive.savedParamValues);
        } else {
          applyPresetToScopeAndLua(FACTORY_DEFAULTS, null, null);
        }
      } else {
        applyPresetToScopeAndLua(FACTORY_DEFAULTS, null, null);
      }

      $scope.toggleCollapse = function () {
        $scope.isCollapsed = !$scope.isCollapsed;
        try {
          localStorage.setItem('realSmoke3D_collapsed', String($scope.isCollapsed));
        } catch (e) {}
        if (typeof $scope.fitHostContainer === 'function') $scope.fitHostContainer();
      };

      $scope.activeTip = null;
      $scope.toggleTip = function (id) {
        $scope.activeTip = ($scope.activeTip === id) ? null : id;
      };
      $scope.showTip = function (id) {
        $scope.activeTip = id;
      };
      $scope.hideTip = function () {
        $scope.activeTip = null;
      };

      $scope.getTempColor = function (temp) {
        if (temp > 120) return '#ff2200';
        if (temp > 80) return '#ff8800';
        if (temp > 50) return '#ffcc00';
        return '#00e5ff';
      };

      function callLua(cmd) {
        try {
          if (window.bngApi && typeof window.bngApi.engineLua === 'function') {
            window.bngApi.engineLua(cmd);
          } else if (typeof bngApi !== 'undefined' && bngApi && typeof bngApi.engineLua === 'function') {
            bngApi.engineLua(cmd);
          }
        } catch (err) {
          if (window.console && console.error) {
            console.error('[VolSmoke UI] callLua failed:', err);
          }
        }
      }

      function normalizeQuality(value) {
        const numericValue = Number(value);
        if (!Number.isFinite(numericValue)) return null;
        const clampedValue = Math.min(QUALITY_MAX, Math.max(QUALITY_MIN, numericValue));
        const steppedValue = Math.round(clampedValue / QUALITY_STEP) * QUALITY_STEP;
        return Number(steppedValue.toFixed(1));
      }

      $scope.onQualityChange = function (val) {
        const raw = (val !== undefined) ? val : $scope.simulationQuality;
        const normalizedValue = normalizeQuality(raw);
        if (normalizedValue === null) return;
        $scope.simulationQuality = normalizedValue;
        $scope.pendingQuality = normalizedValue;
        qualityPendingUntil = Date.now() + QUALITY_PENDING_MS;
        callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setSimulationQuality(' + normalizedValue.toFixed(1) + ')');
        onUserModifiedParam('simulationQuality', normalizedValue);
      };

      function normalizeVoxelMillimeters(value) {
        const numericValue = Number(value);
        if (!Number.isFinite(numericValue)) return null;
        return Math.round(Math.min(VOXEL_MAX_MM, Math.max(VOXEL_MIN_MM, numericValue)));
      }

      $scope.onVoxelChange = function (val) {
        const raw = (val !== undefined) ? val : $scope.voxelMillimeters;
        const normalizedValue = normalizeVoxelMillimeters(raw);
        if (normalizedValue === null) return;
        $scope.voxelMillimeters = normalizedValue;
        voxelPendingUntil = Date.now() + VOXEL_PENDING_MS;
        const meters = (normalizedValue / 1000).toFixed(3);
        callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setVoxelSize(' + meters + ')');
        onUserModifiedParam('voxelMillimeters', normalizedValue);
      };

      function normalizeDomainSize(value) {
        const numericValue = Number(value);
        if (!Number.isFinite(numericValue)) return null;
        const clamped = Math.min(DOMAIN_MAX_M, Math.max(DOMAIN_MIN_M, numericValue));
        return Number(clamped.toFixed(2));
      }

      $scope.onDomainSizeChange = function (val) {
        const raw = (val !== undefined) ? val : $scope.domainSize;
        const normalizedValue = normalizeDomainSize(raw);
        if (normalizedValue === null) return;
        $scope.domainSize = normalizedValue;
        domainPendingUntil = Date.now() + DOMAIN_PENDING_MS;
        callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setDomainSize(' + normalizedValue.toFixed(2) + ')');
        onUserModifiedParam('domainSize', normalizedValue);
      };

      // Physics and Equity sliders interaction
      $scope.onPhysicsChange = function (param, val) {
        if (param === 'smokeColor' || param === 'dustColor') {
          let col = (val !== undefined) ? val : $scope[param];
          if (typeof col === 'string' && col.startsWith('#')) {
            const hex = col.substring(1);
            if (hex.length === 6) {
              col = [
                parseInt(hex.substring(0, 2), 16) / 255.0,
                parseInt(hex.substring(2, 4), 16) / 255.0,
                parseInt(hex.substring(4, 6), 16) / 255.0
              ];
            }
          }
          if (Array.isArray(col) && col.length >= 3) {
            const r = Math.max(0.0, Math.min(1.0, Number(col[0]) != null ? Number(col[0]) : 1.0));
            const g = Math.max(0.0, Math.min(1.0, Number(col[1]) != null ? Number(col[1]) : 1.0));
            const b = Math.max(0.0, Math.min(1.0, Number(col[2]) != null ? Number(col[2]) : 1.0));
            $scope[param] = [r, g, b];
            physicsPendingUntil = Date.now() + 2500;
            callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setPhysicsParam("' + param + '", {' + r.toFixed(3) + ', ' + g.toFixed(3) + ', ' + b.toFixed(3) + '})');
            onUserModifiedParam(param, [r, g, b]);
          }
          return;
        }
        if ($scope.paramEnabled && $scope.paramEnabled[param] === false) {
          $scope.paramEnabled[param] = true;
          delete $scope.savedParamValues[param];
        }
        const raw = (val !== undefined) ? val : $scope[param];
        const numVal = Number(raw);
        if (!Number.isFinite(numVal)) return;
        $scope[param] = numVal;
        const activeProf = ($scope.activeSurfaceProfile === 'sand') ? 'sand' : 'asphalt';
        if (SURFACE_SHARED_PARAMS.indexOf(param) !== -1) {
          if (!$scope.surfaceParams[activeProf]) $scope.surfaceParams[activeProf] = {};
          $scope.surfaceParams[activeProf][param] = numVal;
          if (!$scope.surfaceParamEnabled[activeProf]) $scope.surfaceParamEnabled[activeProf] = {};
          $scope.surfaceParamEnabled[activeProf][param] = true;
          if ($scope.surfaceSavedParamValues[activeProf]) {
            delete $scope.surfaceSavedParamValues[activeProf][param];
          }
        }
        physicsPendingUntil = Date.now() + PHYSICS_PENDING_MS;
        callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setPhysicsParam("' + param + '", ' + numVal.toFixed(2) + ')');
        onUserModifiedParam(param, numVal);
      };

      const SECTION_PARAM_MAP = {
        optics: ['smokeColor', 'dustColor', 'hazeNormals', 'creviceShadow', 'coreOpacity', 'vorticityDetail'],
        equity: ['dustColor', 'heatThreshold', 'frictionSens', 'frictionTime', 'smokeOnset', 'smokeOnsetBezier', 'smokeDecay', 'smokeDecayBezier', 'sandDustScale', 'sandDustSens', 'asphaltSmokeEnabled', 'sandDustEnabled', 'activeSurfaceProfile'],
        wheel: ['treadSaturation', 'treadCoupling', 'edgeDispersion'],
        turb: ['turbTransition', 'turbRelax', 'turbScale1', 'turbStrength1', 'turbScale2', 'turbStrength2', 'turbArch', 'turbArchScale', 'microFiber', 'fiberScale'],
        trail: ['coreLifetime', 'dispersionRate', 'underbodyEject', 'archEject', 'roadDamping', 'smokeDrag', 'thermalBuoyancy'],
        slipstream: ['slipstream', 'slipstreamSpeedLimit', 'slipstreamHoldTime', 'slipstreamBezier', 'slipstreamTurbScale', 'slipstreamTurbStrength'],
        grid: ['simulationQuality', 'voxelMillimeters', 'domainSize']
      };


      // --- Photoshop-Style Color Picker Implementation ---
      function rgbToHex(r, g, b) {
        var hr = Math.max(0, Math.min(255, Math.round(r))).toString(16).padStart(2, '0');
        var hg = Math.max(0, Math.min(255, Math.round(g))).toString(16).padStart(2, '0');
        var hb = Math.max(0, Math.min(255, Math.round(b))).toString(16).padStart(2, '0');
        return ('#' + hr + hg + hb).toUpperCase();
      }

      function hexToRgb(hex) {
        var clean = (hex || '').replace('#', '').trim();
        if (clean.length === 3) {
          clean = clean[0] + clean[0] + clean[1] + clean[1] + clean[2] + clean[2];
        }
        if (clean.length !== 6) return null;
        var r = parseInt(clean.substring(0, 2), 16);
        var g = parseInt(clean.substring(2, 4), 16);
        var b = parseInt(clean.substring(4, 6), 16);
        if (isNaN(r) || isNaN(g) || isNaN(b)) return null;
        return [r, g, b];
      }

      $scope.getSmokeColorCss = function () {
        var sc = $scope.smokeColor;
        var r = (sc && Number.isFinite(Number(sc[0]))) ? Number(sc[0]) : 1.0;
        var g = (sc && Number.isFinite(Number(sc[1]))) ? Number(sc[1]) : 1.0;
        var b = (sc && Number.isFinite(Number(sc[2]))) ? Number(sc[2]) : 1.0;
        return 'rgb(' + Math.round(r * 255) + ',' +
                        Math.round(g * 255) + ',' +
                        Math.round(b * 255) + ')';
      };

      $scope.getSmokeColorHex = function () {
        var sc = $scope.smokeColor;
        var r = (sc && Number.isFinite(Number(sc[0]))) ? Number(sc[0]) : 1.0;
        var g = (sc && Number.isFinite(Number(sc[1]))) ? Number(sc[1]) : 1.0;
        var b = (sc && Number.isFinite(Number(sc[2]))) ? Number(sc[2]) : 1.0;
        return rgbToHex(r * 255, g * 255, b * 255);
      };

      $scope.getPickerCss = function () {
        return 'rgb(' + $scope.pickerR + ',' + $scope.pickerG + ',' + $scope.pickerB + ')';
      };

      $scope.getInitialColorCss = function () {
        var ic = $scope.initialColor || [1, 1, 1];
        return 'rgb(' + Math.round((ic[0] != null ? ic[0] : 1) * 255) + ',' +
                        Math.round((ic[1] != null ? ic[1] : 1) * 255) + ',' +
                        Math.round((ic[2] != null ? ic[2] : 1) * 255) + ')';
      };


      $scope.getSlipstreamP1X = function () {
        return 30 + 200 * Math.max(0, Math.min(1, numOr($scope.slipstreamBezier && $scope.slipstreamBezier.x1, 1.0)));
      };
      $scope.getSlipstreamP1Y = function () {
        return 120 - 100 * Math.max(0, Math.min(1, numOr($scope.slipstreamBezier && $scope.slipstreamBezier.y1, 1.0)));
      };
      $scope.getSlipstreamP2X = function () {
        return 30 + 200 * Math.max(0, Math.min(1, numOr($scope.slipstreamBezier && $scope.slipstreamBezier.x2, 1.0)));
      };
      $scope.getSlipstreamP2Y = function () {
        return 120 - 100 * Math.max(0, Math.min(1, numOr($scope.slipstreamBezier && $scope.slipstreamBezier.y2, 0.0)));
      };

      $scope.toggleBezierEditor = function () {
        $scope.showBezierEditor = !$scope.showBezierEditor;
      };

      $scope.setBezierPreset = function (x1, y1, x2, y2) {
        $scope.slipstreamBezier.x1 = Number(x1);
        $scope.slipstreamBezier.y1 = Number(y1);
        $scope.slipstreamBezier.x2 = Number(x2);
        $scope.slipstreamBezier.y2 = Number(y2);
        $scope.syncBezierToLua();
        onUserModifiedParam('slipstreamBezier', Object.assign({}, $scope.slipstreamBezier));
      };

      $scope.onBezierManualChange = function () {
        $scope.syncBezierToLua();
        onUserModifiedParam('slipstreamBezier', Object.assign({}, $scope.slipstreamBezier));
      };

      var activeCurveType = null;
      var activeBezierSvg = null;

      function onGlobalBezierMouseMove(event) {
        if (!activeCurveType) return;
        if (event.buttons !== undefined && (event.buttons & 1) === 0) {
          onGlobalBezierMouseUp(event);
          return;
        }
        const svg = activeBezierSvg || (event.currentTarget && (event.currentTarget.ownerSVGElement || event.currentTarget.closest('svg')));
        if (!svg) return;
        const rect = svg.getBoundingClientRect();
        if (rect.width <= 0 || rect.height <= 0) return;

        if (activeCurveType === 'onset') {
          const rawX = (event.clientX - rect.left) / rect.width * 250;
          const rawY = (event.clientY - rect.top) / rect.height * 160;

          if ($scope.activeSmokeOnsetBezierDrag === 0) {
            const tempFrac = Math.max(0, Math.min(1, (rawX - 30) / 200));
            const tDeg = 40 + tempFrac * 180;
            const maxX = ($scope.smokeOnsetBezier && $scope.smokeOnsetBezier.x3 !== undefined) ? ($scope.smokeOnsetBezier.x3 - 5) : 220;
            $scope.smokeOnsetBezier.x0 = Math.round(Math.max(40, Math.min(maxX, tDeg)));
            $scope.heatThreshold = $scope.smokeOnsetBezier.x0;
            const hazeFrac = Math.max(0.00, Math.min(1.00, (120 - rawY) / 100));
            $scope.smokeOnsetBezier.y0 = Math.round(hazeFrac * 100) / 100;
          } else if ($scope.activeSmokeOnsetBezierDrag === 1) {
            const p0x = $scope.getBezierP0X();
            const p3x = $scope.getBezierP3X();
            const nx = Math.max(0, Math.min(1, (rawX - p0x) / Math.max(1, p3x - p0x)));
            const ny = Math.max(0, Math.min(1, (120 - rawY) / 100));
            $scope.smokeOnsetBezier.x1 = Math.round(nx * 50) / 50;
            $scope.smokeOnsetBezier.y1 = Math.round(ny * 50) / 50;
          } else if ($scope.activeSmokeOnsetBezierDrag === 2) {
            const p0x = $scope.getBezierP0X();
            const p3x = $scope.getBezierP3X();
            const nx = Math.max(0, Math.min(1, (rawX - p0x) / Math.max(1, p3x - p0x)));
            const ny = Math.max(0, Math.min(1, (120 - rawY) / 100));
            $scope.smokeOnsetBezier.x2 = Math.round(nx * 50) / 50;
            $scope.smokeOnsetBezier.y2 = Math.round(ny * 50) / 50;
          } else if ($scope.activeSmokeOnsetBezierDrag === 3) {
            const tempFrac = Math.max(0, Math.min(1, (rawX - 30) / 200));
            const tDeg = 40 + tempFrac * 180;
            const minX = ($scope.smokeOnsetBezier && $scope.smokeOnsetBezier.x0 !== undefined) ? ($scope.smokeOnsetBezier.x0 + 5) : 45;
            $scope.smokeOnsetBezier.x3 = Math.round(Math.max(minX, Math.min(240, tDeg)));
            const densityFrac = Math.max(0.00, Math.min(1.00, (120 - rawY) / 100));
            $scope.smokeOnsetBezier.y3 = Math.round(densityFrac * 100) / 100;
          }
          $scope.syncSmokeOnsetBezierToLua();
        } else if (activeCurveType === 'decay') {
          const rawX = (event.clientX - rect.left) / rect.width * 250;
          const rawY = (event.clientY - rect.top) / rect.height * 160;

          if ($scope.activeDecayBezierDrag === 0) {
            const fracY = Math.max(0.00, Math.min(1.00, (120 - rawY) / 100));
            $scope.smokeDecayBezier.y0 = Math.round(fracY * 100) / 100;
          } else if ($scope.activeDecayBezierDrag === 3) {
            const frac = Math.max(0.00, Math.min(1.0, (rawX - 30) / 200));
            $scope.smokeDecayBezier.duration = Math.round(frac * 50) / 10;
            $scope.smokeDecay = $scope.smokeDecayBezier.duration;
          } else if ($scope.activeDecayBezierDrag === 1) {
            const p3x = $scope.getDecayP3X();
            const span = Math.max(1, p3x - 30);
            const nx = Math.max(0, Math.min(1, (rawX - 30) / span));
            const ny = Math.max(0, Math.min(1, (120 - rawY) / 100));
            $scope.smokeDecayBezier.x1 = Math.round(nx * 50) / 50;
            $scope.smokeDecayBezier.y1 = Math.round(ny * 50) / 50;
          } else if ($scope.activeDecayBezierDrag === 2) {
            const p3x = $scope.getDecayP3X();
            const span = Math.max(1, p3x - 30);
            const nx = Math.max(0, Math.min(1, (rawX - 30) / span));
            const ny = Math.max(0, Math.min(1, (120 - rawY) / 100));
            $scope.smokeDecayBezier.x2 = Math.round(nx * 50) / 50;
            $scope.smokeDecayBezier.y2 = Math.round(ny * 50) / 50;
          }
          $scope.syncSmokeDecayBezierToLua();
        } else if (activeCurveType === 'slipstream') {
          const rawX = (event.clientX - rect.left) / rect.width * 250;
          const rawY = (event.clientY - rect.top) / rect.height * 160;
          const nx = Math.max(0, Math.min(1, (rawX - 30) / 200));
          const ny = Math.max(0, Math.min(1, (120 - rawY) / 100));

          if ($scope.activeBezierDrag === 1) {
            $scope.slipstreamBezier.x1 = Math.round(nx * 50) / 50;
            $scope.slipstreamBezier.y1 = Math.round(ny * 50) / 50;
          } else if ($scope.activeBezierDrag === 2) {
            $scope.slipstreamBezier.x2 = Math.round(nx * 50) / 50;
            $scope.slipstreamBezier.y2 = Math.round(ny * 50) / 50;
          }
          $scope.syncBezierToLua();
        }
        $scope.$evalAsync();
      }

      function onGlobalBezierMouseUp(event) {
        if (!activeCurveType) return;
        window.removeEventListener('mousemove', onGlobalBezierMouseMove);
        window.removeEventListener('mouseup', onGlobalBezierMouseUp);

        if (activeCurveType === 'onset') {
          $scope.activeSmokeOnsetBezierDrag = null;
          onUserModifiedParam('smokeOnsetBezier', Object.assign({}, $scope.smokeOnsetBezier));
          onUserModifiedParam('heatThreshold', $scope.smokeOnsetBezier.x0);
        } else if (activeCurveType === 'decay') {
          $scope.activeDecayBezierDrag = null;
          onUserModifiedParam('smokeDecayBezier', Object.assign({}, $scope.smokeDecayBezier));
          onUserModifiedParam('smokeDecay', $scope.smokeDecayBezier.duration);
        } else if (activeCurveType === 'slipstream') {
          $scope.activeBezierDrag = null;
          onUserModifiedParam('slipstreamBezier', Object.assign({}, $scope.slipstreamBezier));
        }

        activeCurveType = null;
        activeBezierSvg = null;
        $scope.$evalAsync();
      }

      $scope.startDragBezier = function (pointIndex, event) {
        $scope.activeBezierDrag = pointIndex;
        activeCurveType = 'slipstream';
        activeBezierSvg = (event && event.currentTarget) ? (event.currentTarget.ownerSVGElement || event.currentTarget.closest('svg')) : null;
        window.removeEventListener('mousemove', onGlobalBezierMouseMove);
        window.removeEventListener('mouseup', onGlobalBezierMouseUp);
        window.addEventListener('mousemove', onGlobalBezierMouseMove);
        window.addEventListener('mouseup', onGlobalBezierMouseUp);
        if (event) {
          event.preventDefault();
          event.stopPropagation();
        }
      };

      $scope.stopDragBezier = function () {
        if ($scope.activeBezierDrag) {
          onGlobalBezierMouseUp();
        }
      };

      $scope.onDragBezier = function (event) {
        onGlobalBezierMouseMove(event);
      };

      $scope.syncBezierToLua = function () {
        physicsPendingUntil = Date.now() + PHYSICS_PENDING_MS;
        const b = $scope.slipstreamBezier;
        callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setSlipstreamBezier(' +
          numOr(b.x1, 1.0).toFixed(2) + ', ' + numOr(b.y1, 1.0).toFixed(2) + ', ' +
          numOr(b.x2, 1.0).toFixed(2) + ', ' + numOr(b.y2, 0.0).toFixed(2) + ')');
      };

      // Thermal Smoke Onset S-Curve (Section 2) with Interactive P0 Onset Handle
      $scope.toggleSmokeOnsetBezierEditor = function () {
        $scope.showSmokeOnsetBezierEditor = !$scope.showSmokeOnsetBezierEditor;
      };

      $scope.getBezierP0X = function () {
        var x0 = ($scope.smokeOnsetBezier && $scope.smokeOnsetBezier.x0 !== undefined) ? Number($scope.smokeOnsetBezier.x0) : 70;
        return 30 + 200 * Math.max(0, Math.min(1, (x0 - 40) / 180));
      };

      $scope.getBezierP0Y = function () {
        var y0 = ($scope.smokeOnsetBezier && $scope.smokeOnsetBezier.y0 !== undefined) ? Number($scope.smokeOnsetBezier.y0) : 0.0;
        return 120 - 100 * Math.max(0, Math.min(1.00, y0));
      };

      $scope.getBezierP3X = function () {
        var x3 = ($scope.smokeOnsetBezier && $scope.smokeOnsetBezier.x3 !== undefined) ? Number($scope.smokeOnsetBezier.x3) : 220;
        return 30 + 200 * Math.max(0, Math.min(1, (x3 - 40) / 180));
      };

      $scope.getBezierP3Y = function () {
        var y3 = ($scope.smokeOnsetBezier && $scope.smokeOnsetBezier.y3 !== undefined) ? Number($scope.smokeOnsetBezier.y3) : 1.0;
        return 120 - 100 * Math.max(0.00, Math.min(1.0, y3));
      };

      $scope.getBezierP1X = function () {
        var p0x = $scope.getBezierP0X();
        var p3x = $scope.getBezierP3X();
        var x1 = ($scope.smokeOnsetBezier && $scope.smokeOnsetBezier.x1 !== undefined) ? Number($scope.smokeOnsetBezier.x1) : 0.25;
        return p0x + (p3x - p0x) * Math.max(0, Math.min(1, x1));
      };

      $scope.getBezierP1Y = function () {
        var y1 = ($scope.smokeOnsetBezier && $scope.smokeOnsetBezier.y1 !== undefined) ? Number($scope.smokeOnsetBezier.y1) : 0.05;
        return 120 - 100 * Math.max(0, Math.min(1, y1));
      };

      $scope.getBezierP2X = function () {
        var p0x = $scope.getBezierP0X();
        var p3x = $scope.getBezierP3X();
        var x2 = ($scope.smokeOnsetBezier && $scope.smokeOnsetBezier.x2 !== undefined) ? Number($scope.smokeOnsetBezier.x2) : 0.55;
        return p0x + (p3x - p0x) * Math.max(0, Math.min(1, x2));
      };

      $scope.getBezierP2Y = function () {
        var y2 = ($scope.smokeOnsetBezier && $scope.smokeOnsetBezier.y2 !== undefined) ? Number($scope.smokeOnsetBezier.y2) : 0.95;
        return 120 - 100 * Math.max(0, Math.min(1, y2));
      };

      $scope.setSmokeOnsetBezierPreset = function (x0, y0, x1, y1, x2, y2) {
        $scope.smokeOnsetBezier.x0 = Number(x0);
        $scope.smokeOnsetBezier.y0 = Number(y0);
        $scope.smokeOnsetBezier.x1 = Number(x1);
        $scope.smokeOnsetBezier.y1 = Number(y1);
        $scope.smokeOnsetBezier.x2 = Number(x2);
        $scope.smokeOnsetBezier.y2 = Number(y2);
        $scope.syncSmokeOnsetBezierToLua();
        onUserModifiedParam('smokeOnsetBezier', Object.assign({}, $scope.smokeOnsetBezier));
      };

      $scope.onSmokeOnsetBezierManualChange = function () {
        $scope.syncSmokeOnsetBezierToLua();
        onUserModifiedParam('smokeOnsetBezier', Object.assign({}, $scope.smokeOnsetBezier));
      };

      $scope.startDragSmokeOnsetBezier = function (pointIndex, event) {
        $scope.activeSmokeOnsetBezierDrag = pointIndex;
        activeCurveType = 'onset';
        activeBezierSvg = (event && event.currentTarget) ? (event.currentTarget.ownerSVGElement || event.currentTarget.closest('svg')) : null;
        window.removeEventListener('mousemove', onGlobalBezierMouseMove);
        window.removeEventListener('mouseup', onGlobalBezierMouseUp);
        window.addEventListener('mousemove', onGlobalBezierMouseMove);
        window.addEventListener('mouseup', onGlobalBezierMouseUp);
        if (event) {
          event.preventDefault();
          event.stopPropagation();
        }
      };

      $scope.stopDragSmokeOnsetBezier = function () {
        if ($scope.activeSmokeOnsetBezierDrag !== null && $scope.activeSmokeOnsetBezierDrag !== undefined) {
          onGlobalBezierMouseUp();
        }
      };

      $scope.onDragSmokeOnsetBezier = function (event) {
        onGlobalBezierMouseMove(event);
      };

      $scope.syncSmokeOnsetBezierToLua = function () {
        physicsPendingUntil = Date.now() + PHYSICS_PENDING_MS;
        const b = $scope.smokeOnsetBezier;
        callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setSmokeOnsetBezier(' +
          numOr(b.x0, 70).toFixed(1) + ', ' +
          numOr(b.y0, 0.0).toFixed(2) + ', ' +
          numOr(b.x1, 0.25).toFixed(2) + ', ' +
          numOr(b.y1, 0.05).toFixed(2) + ', ' +
          numOr(b.x2, 0.55).toFixed(2) + ', ' +
          numOr(b.y2, 0.95).toFixed(2) + ', ' +
          numOr(b.x3, 220).toFixed(1) + ', ' +
          numOr(b.y3, 1.00).toFixed(2) + ')');
      };

      $scope.toggleDecayBezierEditor = function () {
        $scope.showDecayBezierEditor = !$scope.showDecayBezierEditor;
      };

      $scope.getDecayP0Y = function () {
        const y0 = numOr($scope.smokeDecayBezier && $scope.smokeDecayBezier.y0, 1.00);
        return 120 - 100 * Math.max(0.00, Math.min(1.00, y0));
      };

      $scope.getDecayP3X = function () {
        const dur = numOr($scope.smokeDecayBezier && $scope.smokeDecayBezier.duration, 1.50);
        const durClamped = Math.max(0.0, Math.min(5.0, dur));
        return 30 + 200 * (durClamped / 5.0);
      };

      $scope.getDecayP1X = function () {
        const p3x = $scope.getDecayP3X();
        const x1 = numOr($scope.smokeDecayBezier && $scope.smokeDecayBezier.x1, 0.25);
        return 30 + Math.max(1, p3x - 30) * Math.max(0, Math.min(1, x1));
      };

      $scope.getDecayP1Y = function () {
        const y1 = numOr($scope.smokeDecayBezier && $scope.smokeDecayBezier.y1, 0.95);
        return 120 - 100 * Math.max(0, Math.min(1, y1));
      };

      $scope.getDecayP2X = function () {
        const p3x = $scope.getDecayP3X();
        const x2 = numOr($scope.smokeDecayBezier && $scope.smokeDecayBezier.x2, 0.65);
        return 30 + Math.max(1, p3x - 30) * Math.max(0, Math.min(1, x2));
      };

      $scope.getDecayP2Y = function () {
        const y2 = numOr($scope.smokeDecayBezier && $scope.smokeDecayBezier.y2, 0.15);
        return 120 - 100 * Math.max(0, Math.min(1, y2));
      };

      $scope.startDragSmokeDecayBezier = function (pointIndex, event) {
        $scope.activeDecayBezierDrag = pointIndex;
        activeCurveType = 'decay';
        activeBezierSvg = (event && event.currentTarget) ? (event.currentTarget.ownerSVGElement || event.currentTarget.closest('svg')) : null;
        window.removeEventListener('mousemove', onGlobalBezierMouseMove);
        window.removeEventListener('mouseup', onGlobalBezierMouseUp);
        window.addEventListener('mousemove', onGlobalBezierMouseMove);
        window.addEventListener('mouseup', onGlobalBezierMouseUp);
        if (event) {
          event.preventDefault();
          event.stopPropagation();
        }
      };

      $scope.stopDragSmokeDecayBezier = function () {
        if ($scope.activeDecayBezierDrag !== null && $scope.activeDecayBezierDrag !== undefined) {
          onGlobalBezierMouseUp();
        }
      };

      $scope.onDragSmokeDecayBezier = function (event) {
        onGlobalBezierMouseMove(event);
      };

      $scope.syncSmokeDecayBezierToLua = function () {
        physicsPendingUntil = Date.now() + PHYSICS_PENDING_MS;
        const b = $scope.smokeDecayBezier;
        const dur = numOr(b.duration, 1.50).toFixed(2);
        const y0 = numOr(b.y0, 1.00).toFixed(2);
        const x1 = numOr(b.x1, 0.25).toFixed(2);
        const y1 = numOr(b.y1, 0.95).toFixed(2);
        const x2 = numOr(b.x2, 0.65).toFixed(2);
        const y2 = numOr(b.y2, 0.15).toFixed(2);
        callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setSmokeDecayBezier(' + dur + ', ' + y0 + ', ' + x1 + ', ' + y1 + ', ' + x2 + ', ' + y2 + ')');
      };

      $scope.resetSmokeColor = function () {
        $scope.smokeColor = [1.0, 1.0, 1.0];
        $scope.onPhysicsChange('smokeColor', $scope.smokeColor);
      };

      var canvasMoveHandler = null;
      var canvasUpHandler = null;

      function initColorPickerCanvases() {
        var specEl = document.getElementById('rs-spectrum-canvas');
        var grayEl = document.getElementById('rs-gray-canvas');
        if (!specEl || !grayEl) return;

        var sCtx = specEl.getContext('2d');
        var gCtx = grayEl.getContext('2d');
        var sw = specEl.width;
        var sh = specEl.height;
        var gw = grayEl.width;
        var gh = grayEl.height;

        // 1. Spectrum: Rainbow Hue horizontally
        var gradH = sCtx.createLinearGradient(0, 0, sw, 0);
        gradH.addColorStop(0.00, '#ff0000');
        gradH.addColorStop(0.17, '#ffff00');
        gradH.addColorStop(0.33, '#00ff00');
        gradH.addColorStop(0.50, '#00ffff');
        gradH.addColorStop(0.67, '#0000ff');
        gradH.addColorStop(0.83, '#ff00ff');
        gradH.addColorStop(1.00, '#ff0000');
        sCtx.fillStyle = gradH;
        sCtx.fillRect(0, 0, sw, sh);

        // Vertical overlay: White on top half, Black on bottom half
        var gradVWhite = sCtx.createLinearGradient(0, 0, 0, sh * 0.5);
        gradVWhite.addColorStop(0.0, 'rgba(255, 255, 255, 1.0)');
        gradVWhite.addColorStop(1.0, 'rgba(255, 255, 255, 0.0)');
        sCtx.fillStyle = gradVWhite;
        sCtx.fillRect(0, 0, sw, sh * 0.5);

        var gradVBlack = sCtx.createLinearGradient(0, sh * 0.5, 0, sh);
        gradVBlack.addColorStop(0.0, 'rgba(0, 0, 0, 0.0)');
        gradVBlack.addColorStop(1.0, 'rgba(0, 0, 0, 1.0)');
        sCtx.fillStyle = gradVBlack;
        sCtx.fillRect(0, sh * 0.5, sw, sh * 0.5);

        // 2. Grayscale Bar: 0% black to 100% white
        var gradGray = gCtx.createLinearGradient(0, 0, gw, 0);
        gradGray.addColorStop(0.0, '#000000');
        gradGray.addColorStop(1.0, '#ffffff');
        gCtx.fillStyle = gradGray;
        gCtx.fillRect(0, 0, gw, gh);

        var isDraggingSpec = false;
        var isDraggingGray = false;

        function pickSpec(e) {
          var rect = specEl.getBoundingClientRect();
          var x = Math.max(0, Math.min(sw - 1, Math.floor((e.clientX - rect.left) * (sw / rect.width))));
          var y = Math.max(0, Math.min(sh - 1, Math.floor((e.clientY - rect.top) * (sh / rect.height))));
          var p = sCtx.getImageData(x, y, 1, 1).data;
          $scope.$applyAsync(function () {
            $scope.pickerR = p[0];
            $scope.pickerG = p[1];
            $scope.pickerB = p[2];
            $scope.pickerHex = rgbToHex(p[0], p[1], p[2]);
            $scope.pickerPointerX = (x / sw) * 100;
            $scope.pickerPointerY = (y / sh) * 100;
            $scope.showPointer = true;
          });
        }

        function pickGray(e) {
          var rect = grayEl.getBoundingClientRect();
          var x = Math.max(0, Math.min(gw - 1, Math.floor((e.clientX - rect.left) * (gw / rect.width))));
          var p = gCtx.getImageData(x, 0, 1, 1).data;
          $scope.$applyAsync(function () {
            $scope.pickerR = p[0];
            $scope.pickerG = p[1];
            $scope.pickerB = p[2];
            $scope.pickerHex = rgbToHex(p[0], p[1], p[2]);
            $scope.showPointer = false;
          });
        }

        specEl.onmousedown = function (e) {
          isDraggingSpec = true;
          pickSpec(e);
        };
        grayEl.onmousedown = function (e) {
          isDraggingGray = true;
          pickGray(e);
        };

        if (canvasMoveHandler) window.removeEventListener('mousemove', canvasMoveHandler);
        if (canvasUpHandler) window.removeEventListener('mouseup', canvasUpHandler);

        canvasMoveHandler = function (e) {
          if (isDraggingSpec) pickSpec(e);
          else if (isDraggingGray) pickGray(e);
        };
        canvasUpHandler = function () {
          isDraggingSpec = false;
          isDraggingGray = false;
        };

        window.addEventListener('mousemove', canvasMoveHandler);
        window.addEventListener('mouseup', canvasUpHandler);
      }

      $scope.getDustColorCss = function () {
        var dc = $scope.dustColor;
        var r = (dc && Number.isFinite(Number(dc[0]))) ? Number(dc[0]) : 0.76;
        var g = (dc && Number.isFinite(Number(dc[1]))) ? Number(dc[1]) : 0.65;
        var b = (dc && Number.isFinite(Number(dc[2]))) ? Number(dc[2]) : 0.50;
        return 'rgb(' + Math.round(r * 255) + ',' +
                        Math.round(g * 255) + ',' +
                        Math.round(b * 255) + ')';
      };

      $scope.getDustColorHex = function () {
        var dc = $scope.dustColor;
        var r = (dc && Number.isFinite(Number(dc[0]))) ? Number(dc[0]) : 0.76;
        var g = (dc && Number.isFinite(Number(dc[1]))) ? Number(dc[1]) : 0.65;
        var b = (dc && Number.isFinite(Number(dc[2]))) ? Number(dc[2]) : 0.50;
        return rgbToHex(r * 255, g * 255, b * 255);
      };

      $scope.resetDustColor = function () {
        $scope.dustColor = [0.76, 0.65, 0.50];
        $scope.onPhysicsChange('dustColor', $scope.dustColor);
      };

      $scope.getPickerModalTitle = function () {
        return ($scope.colorPickerTarget === 'dustColor') ? $scope.t('dustColorPickerTitle') : $scope.t('smokeColorPickerTitle');
      };

      $scope.openColorPicker = function (targetParam) {
        $scope.colorPickerTarget = (targetParam === 'dustColor') ? 'dustColor' : 'smokeColor';
        var fallback = ($scope.colorPickerTarget === 'dustColor') ? [0.76, 0.65, 0.50] : [1.0, 1.0, 1.0];
        var cur = $scope[$scope.colorPickerTarget];
        var r = (cur && Number.isFinite(Number(cur[0]))) ? Number(cur[0]) : fallback[0];
        var g = (cur && Number.isFinite(Number(cur[1]))) ? Number(cur[1]) : fallback[1];
        var b = (cur && Number.isFinite(Number(cur[2]))) ? Number(cur[2]) : fallback[2];
        $scope.initialColor = [r, g, b];
        $scope.pickerR = Math.round(r * 255);
        $scope.pickerG = Math.round(g * 255);
        $scope.pickerB = Math.round(b * 255);
        $scope.pickerHex = rgbToHex($scope.pickerR, $scope.pickerG, $scope.pickerB);
        $scope.showPointer = false;
        $scope.isColorPickerOpen = true;
        setTimeout(initColorPickerCanvases, 40);
      };

      $scope.closeColorPicker = function () {
        $scope.isColorPickerOpen = false;
        if (canvasMoveHandler) window.removeEventListener('mousemove', canvasMoveHandler);
        if (canvasUpHandler) window.removeEventListener('mouseup', canvasUpHandler);
      };

      $scope.applyColorPicker = function () {
        var target = $scope.colorPickerTarget || 'smokeColor';
        var fallback = (target === 'dustColor') ? [0.76, 0.65, 0.50] : [1.0, 1.0, 1.0];
        var r = Number.isFinite($scope.pickerR) ? Math.max(0, Math.min(255, Math.round($scope.pickerR))) / 255.0 : fallback[0];
        var g = Number.isFinite($scope.pickerG) ? Math.max(0, Math.min(255, Math.round($scope.pickerG))) / 255.0 : fallback[1];
        var b = Number.isFinite($scope.pickerB) ? Math.max(0, Math.min(255, Math.round($scope.pickerB))) / 255.0 : fallback[2];
        $scope[target] = [r, g, b];
        $scope.onPhysicsChange(target, $scope[target]);
        $scope.closeColorPicker();
      };

      $scope.revertToInitialColor = function () {
        var fallback = ($scope.colorPickerTarget === 'dustColor') ? [0.76, 0.65, 0.50] : [1.0, 1.0, 1.0];
        var ic = $scope.initialColor;
        var r = (ic && Number.isFinite(Number(ic[0]))) ? Number(ic[0]) : fallback[0];
        var g = (ic && Number.isFinite(Number(ic[1]))) ? Number(ic[1]) : fallback[1];
        var b = (ic && Number.isFinite(Number(ic[2]))) ? Number(ic[2]) : fallback[2];
        $scope.pickerR = Math.round(r * 255);
        $scope.pickerG = Math.round(g * 255);
        $scope.pickerB = Math.round(b * 255);
        $scope.pickerHex = rgbToHex($scope.pickerR, $scope.pickerG, $scope.pickerB);
        $scope.showPointer = false;
      };

      $scope.setPickerDefault = function () {
        if ($scope.colorPickerTarget === 'dustColor') {
          $scope.pickerR = Math.round(0.76 * 255);
          $scope.pickerG = Math.round(0.65 * 255);
          $scope.pickerB = Math.round(0.50 * 255);
          $scope.pickerHex = '#C2A680';
        } else {
          $scope.pickerR = 255;
          $scope.pickerG = 255;
          $scope.pickerB = 255;
          $scope.pickerHex = '#FFFFFF';
        }
        $scope.showPointer = false;
      };

      $scope.onPickerHexChange = function () {
        var rgb = hexToRgb($scope.pickerHex);
        if (rgb) {
          $scope.pickerR = rgb[0];
          $scope.pickerG = rgb[1];
          $scope.pickerB = rgb[2];
        }
      };

      $scope.onPickerRgbChange = function () {
        $scope.pickerR = Math.max(0, Math.min(255, parseInt($scope.pickerR, 10) || 0));
        $scope.pickerG = Math.max(0, Math.min(255, parseInt($scope.pickerG, 10) || 0));
        $scope.pickerB = Math.max(0, Math.min(255, parseInt($scope.pickerB, 10) || 0));
        $scope.pickerHex = rgbToHex($scope.pickerR, $scope.pickerG, $scope.pickerB);
      };

      $scope.resetParam = function (paramKey, $event) {
        if ($event) $event.stopPropagation();
        const defVal = FACTORY_DEFAULTS[paramKey];
        if (defVal === undefined) return;

        if (paramKey === 'simulationQuality') {
          $scope.onQualityChange(defVal);
          qualityPendingUntil = Date.now() + 3500;
        } else if (paramKey === 'voxelMillimeters') {
          $scope.onVoxelChange(defVal);
          voxelPendingUntil = Date.now() + 3500;
        } else if (paramKey === 'domainSize') {
          $scope.onDomainSizeChange(defVal);
          domainPendingUntil = Date.now() + 3500;
        } else if (paramKey === 'smokeOnsetBezier') {
          $scope.smokeOnsetBezier = deepClone(defVal);
          if ($scope.syncSmokeOnsetBezierToLua) $scope.syncSmokeOnsetBezierToLua();
          onUserModifiedParam('smokeOnsetBezier', deepClone(defVal));
          physicsPendingUntil = Date.now() + 3500;
        } else if (paramKey === 'smokeDecayBezier') {
          $scope.smokeDecayBezier = deepClone(defVal);
          if ($scope.syncSmokeDecayBezierToLua) $scope.syncSmokeDecayBezierToLua();
          onUserModifiedParam('smokeDecayBezier', deepClone(defVal));
          physicsPendingUntil = Date.now() + 3500;
        } else if (paramKey === 'slipstreamBezier') {
          $scope.slipstreamBezier = deepClone(defVal);
          if ($scope.syncBezierToLua) $scope.syncBezierToLua();
          onUserModifiedParam('slipstreamBezier', deepClone(defVal));
          physicsPendingUntil = Date.now() + 3500;
        } else {
          $scope.onPhysicsChange(paramKey, defVal);
          physicsPendingUntil = Date.now() + 3500;
        }
        $scope.paramEnabled[paramKey] = true;
        delete $scope.savedParamValues[paramKey];
        const activeProf = ($scope.activeSurfaceProfile === 'sand') ? 'sand' : 'asphalt';
        if (SURFACE_SHARED_PARAMS.indexOf(paramKey) !== -1) {
          if ($scope.surfaceParamEnabled[activeProf]) $scope.surfaceParamEnabled[activeProf][paramKey] = true;
          if ($scope.surfaceSavedParamValues[activeProf]) delete $scope.surfaceSavedParamValues[activeProf][paramKey];
          if ($scope.surfaceParams[activeProf]) $scope.surfaceParams[activeProf][paramKey] = deepClone(defVal);
        }
        savePresetsToStorage();
      };

      $scope.resetSection = function (sectionKey) {
        const keys = SECTION_PARAM_MAP[sectionKey];
        if (!keys || !keys.length) return;

        if (sectionKey === 'grid') {
          $scope.onQualityChange(FACTORY_DEFAULTS.simulationQuality);
          $scope.onVoxelChange(FACTORY_DEFAULTS.voxelMillimeters);
          $scope.onDomainSizeChange(FACTORY_DEFAULTS.domainSize);
          qualityPendingUntil = Date.now() + 3500;
          voxelPendingUntil = Date.now() + 3500;
          domainPendingUntil = Date.now() + 3500;
          savePresetsToStorage();
          return;
        }

        const activeProf = ($scope.activeSurfaceProfile === 'sand') ? 'sand' : 'asphalt';
        for (let i = 0; i < keys.length; i++) {
          const k = keys[i];
          if (k === 'activeSurfaceProfile') continue;
          const def = PARAM_DEFINITIONS[k];
          if (def && def.surface && def.surface !== $scope.activeSurfaceProfile) {
            continue; // Reset ONLY the currently active surface profile (asphalt OR sand)
          }
          const defVal = FACTORY_DEFAULTS[k];
          if (defVal !== undefined) {
            if (k === 'asphaltSmokeEnabled') {
              $scope.asphaltSmokeEnabled = Boolean(defVal);
              callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setAsphaltSmokeEnabled(' + ($scope.asphaltSmokeEnabled ? 'true' : 'false') + ')');
              onUserModifiedParam('asphaltSmokeEnabled', $scope.asphaltSmokeEnabled);
            } else if (k === 'sandDustEnabled') {
              $scope.sandDustEnabled = Boolean(defVal);
              callLua('(realSmoke3DGE or extensions.realSmoke3DGE).setSandDustEnabled(' + ($scope.sandDustEnabled ? 'true' : 'false') + ')');
              onUserModifiedParam('sandDustEnabled', $scope.sandDustEnabled);
            } else if (k === 'smokeOnsetBezier') {
              $scope.smokeOnsetBezier = deepClone(defVal);
              if ($scope.syncSmokeOnsetBezierToLua) $scope.syncSmokeOnsetBezierToLua();
              onUserModifiedParam('smokeOnsetBezier', deepClone(defVal));
            } else if (k === 'smokeDecayBezier') {
              $scope.smokeDecayBezier = deepClone(defVal);
              if ($scope.syncSmokeDecayBezierToLua) $scope.syncSmokeDecayBezierToLua();
              onUserModifiedParam('smokeDecayBezier', deepClone(defVal));
            } else if (k === 'slipstreamBezier') {
              $scope.slipstreamBezier = deepClone(defVal);
              if ($scope.syncBezierToLua) $scope.syncBezierToLua();
              onUserModifiedParam('slipstreamBezier', deepClone(defVal));
            } else {
              $scope.onPhysicsChange(k, defVal);
            }
            $scope.paramEnabled[k] = true;
            delete $scope.savedParamValues[k];
            if (SURFACE_SHARED_PARAMS.indexOf(k) !== -1) {
              if ($scope.surfaceParamEnabled[activeProf]) $scope.surfaceParamEnabled[activeProf][k] = true;
              if ($scope.surfaceSavedParamValues[activeProf]) delete $scope.surfaceSavedParamValues[activeProf][k];
              if ($scope.surfaceParams[activeProf]) $scope.surfaceParams[activeProf][k] = deepClone(defVal);
            }
          }
        }
        physicsPendingUntil = Date.now() + 3500;
        savePresetsToStorage();
      };

      $scope.resetPhysicsDefaults = function () {
        resetSurfaceMapsToFactory();
        applyPresetToScopeAndLua(FACTORY_DEFAULTS, null);
        for (let i = 0; i < toggleableParams.length; i++) {
          $scope.paramEnabled[toggleableParams[i]] = true;
        }
        $scope.savedParamValues = {};
        if ($scope.activePresetId !== 'default') {
          const activeP = $scope.presets.find(function (p) { return p.id === $scope.activePresetId; });
          if (activeP) {
            activeP.params = Object.assign({}, FACTORY_DEFAULTS);
            activeP.paramEnabled = Object.assign({}, $scope.paramEnabled);
            activeP.savedParamValues = {};
            activeP.surfaceParams = deepClone($scope.surfaceParams);
            activeP.surfaceParamEnabled = deepClone($scope.surfaceParamEnabled);
            activeP.surfaceSavedParamValues = deepClone($scope.surfaceSavedParamValues);
            savePresetsToStorage();
          }
        }
        physicsPendingUntil = Date.now() + 2500;
        callLua('if resetRealSmokePhysicsDefaults then resetRealSmokePhysicsDefaults() elseif realSmoke3DGE then realSmoke3DGE.resetPhysicsDefaults() end');
      };

      $scope.getActiveVoxelsFormatted = function () {
        const v = $scope.activeVoxels || 0;
        if (v < 500) {
          return ($scope.lang === 'ru') ? '0 тыс.' : '0 k';
        }
        if ($scope.lang === 'ru') {
          if (v >= 1000000) return (v / 1000000).toFixed(2) + ' млн';
          return Math.round(v / 1000) + ' тыс.';
        } else {
          if (v >= 1000000) return (v / 1000000).toFixed(2) + 'M';
          return Math.round(v / 1000) + 'k';
        }
      };

      function _reset() {
        $scope.$evalAsync(function () {
          $scope.flTemp = 20;
          $scope.frTemp = 20;
          $scope.rlTemp = 20;
          $scope.rrTemp = 20;
          $scope.flSlip = 0.0;
          $scope.frSlip = 0.0;
          $scope.rlSlip = 0.0;
          $scope.rrSlip = 0.0;
          $scope.totalEmission = 0.0;
          $scope.pendingQuality = null;
          qualityPendingUntil = 0;
          voxelPendingUntil = 0;
          physicsPendingUntil = 0;
        });
      }

      $scope.$on('VehicleFocusChanged', _reset);
      $scope.$on('VehicleReset', _reset);

      $scope.$on('VolSmokeTelemetry', function (event, data) {
        if (!data) return;
        $scope.$evalAsync(function () {
          if (data.diagStatus) $scope.diagStatus = data.diagStatus;
          if (data.diagCode) $scope.diagCode = data.diagCode;
          if (data.diagApi) $scope.diagApi = data.diagApi;
          if (data.diagApiLabel) $scope.diagApiLabel = data.diagApiLabel;
          if (data.diagScaled !== undefined) $scope.diagScaled = (data.diagScaled === true);
          if (data.diagScalePct !== undefined) $scope.diagScalePct = data.diagScalePct;
          if (data.diagDepthW !== undefined) $scope.diagDepthW = data.diagDepthW;
          if (data.diagDepthH !== undefined) $scope.diagDepthH = data.diagDepthH;
          if (data.diagFrameW !== undefined) $scope.diagFrameW = data.diagFrameW;
          if (data.diagFrameH !== undefined) $scope.diagFrameH = data.diagFrameH;
          if (data.diagHdr !== undefined) $scope.diagHdr = (data.diagHdr === true);
          if (data.diagUiCaptured !== undefined) $scope.diagUiCaptured = (data.diagUiCaptured === true);
          if (data.conflictingAddon !== undefined) $scope.conflictingAddon = data.conflictingAddon;
          if (data.diagFrames !== undefined) $scope.diagFrames = data.diagFrames;
          if (data.diagFps !== undefined) $scope.diagFps = data.diagFps;
          if (data.diagFpsAvg !== undefined) $scope.diagFpsAvg = data.diagFpsAvg;
          if (data.diagFpsMin !== undefined) $scope.diagFpsMin = data.diagFpsMin;
          if (data.diagFrameMs !== undefined) $scope.diagFrameMs = data.diagFrameMs;
          if (data.diagGpuMs !== undefined) $scope.diagGpuMs = data.diagGpuMs;
          if (data.particleConflict !== undefined) $scope.particleConflict = (data.particleConflict === true);
          if (data.particleConflictMod !== undefined) $scope.particleConflictMod = data.particleConflictMod;
          if (data.particleSuppressed !== undefined) $scope.particleSuppressed = (data.particleSuppressed === true);

          if (!data.wheels) return;
          const fl = data.wheels.FL || {};
          const fr = data.wheels.FR || {};
          const rl = data.wheels.RL || {};
          const rr = data.wheels.RR || {};
          $scope.flTemp = fl.contactPatchTemperature || fl.temperature || 20;
          $scope.frTemp = fr.contactPatchTemperature || fr.temperature || 20;
          $scope.rlTemp = rl.contactPatchTemperature || rl.temperature || 20;
          $scope.rrTemp = rr.contactPatchTemperature || rr.temperature || 20;
          $scope.flSlip = fl.slip || 0;
          $scope.frSlip = fr.slip || 0;
          $scope.rlSlip = rl.slip || 0;
          $scope.rrSlip = rr.slip || 0;
          $scope.totalEmission = Math.min(1, Math.max(0, data.totalEmission || 0));

          // Dynamic live active voxel estimation
          const emission = $scope.totalEmission;
          if (emission > 0.01) {
            const targetFrac = Math.min(0.85, emission * 0.90);
            $scope.activeSmokeFraction = ($scope.activeSmokeFraction || 0) + (targetFrac - ($scope.activeSmokeFraction || 0)) * 0.18;
          } else {
            $scope.activeSmokeFraction = Math.max(0, ($scope.activeSmokeFraction || 0) - 0.015);
          }
          const totalGridVoxels = ($scope.gridWidth || 160) * ($scope.gridHeight || 160) * ($scope.gridDepth || 60);
          $scope.activeVoxels = Math.round($scope.activeSmokeFraction * totalGridVoxels);

          const now = Date.now();

          // Simulation quality sync (respecting pending debounce)
          const telemetryQuality = normalizeQuality(data.simulationQuality || data.quality);
          if (telemetryQuality !== null) {
            const pendingActive = $scope.pendingQuality !== null && now < qualityPendingUntil;
            if (pendingActive) {
              if (Math.abs(telemetryQuality - $scope.pendingQuality) < 0.05) {
                $scope.simulationQuality = $scope.pendingQuality;
                $scope.pendingQuality = null;
                qualityPendingUntil = 0;
              }
            } else {
              $scope.pendingQuality = null;
              qualityPendingUntil = 0;
              $scope.simulationQuality = telemetryQuality;
            }
          }

          // Voxel size sync (respecting pending debounce)
          const telemetryVoxelMm = normalizeVoxelMillimeters(Number(data.voxelSize) * 1000);
          if (telemetryVoxelMm !== null && now >= voxelPendingUntil) {
            $scope.voxelMillimeters = telemetryVoxelMm;
          }

          // Domain size sync (respecting pending debounce)
          if (now >= domainPendingUntil) {
            if (Number.isFinite(Number(data.domainSize))) {
              $scope.domainSize = Number(data.domainSize);
            } else if (Number.isFinite(Number(data.domainX))) {
              $scope.domainSize = Number(data.domainX);
            }
          }

          if (Number.isFinite(Number(data.gridWidth))) $scope.gridWidth = Number(data.gridWidth);
          if (Number.isFinite(Number(data.gridHeight))) $scope.gridHeight = Number(data.gridHeight);
          if (Number.isFinite(Number(data.gridDepth))) $scope.gridDepth = Number(data.gridDepth);
          if (Number.isFinite(Number(data.domainX))) $scope.domainX = Number(data.domainX);
          if (Number.isFinite(Number(data.domainY))) $scope.domainY = Number(data.domainY);
          if (Number.isFinite(Number(data.domainZ))) $scope.domainZ = Number(data.domainZ);

          // Physics & Equity tuning sync (respecting pending debounce and bypass state)
          if (now >= physicsPendingUntil) {
            if ($scope.isParamEnabled('heatThreshold') && Number.isFinite(Number(data.heatThreshold))) $scope.heatThreshold = Number(data.heatThreshold);
            if ($scope.isParamEnabled('frictionSens') && Number.isFinite(Number(data.frictionSens))) $scope.frictionSens = Number(data.frictionSens);
            if ($scope.isParamEnabled('frictionTime') && Number.isFinite(Number(data.frictionTime))) $scope.frictionTime = Number(data.frictionTime);
            if ($scope.isParamEnabled('smokeOnset') && Number.isFinite(Number(data.smokeOnset))) $scope.smokeOnset = Number(data.smokeOnset);
            if ($scope.isParamEnabled('smokeDecay') && Number.isFinite(Number(data.smokeDecay))) $scope.smokeDecay = Number(data.smokeDecay);
            if (data.activeSurfaceProfile !== undefined && (data.activeSurfaceProfile === 'asphalt' || data.activeSurfaceProfile === 'sand')) {
              if ($scope.activeSurfaceProfile !== data.activeSurfaceProfile) {
                saveCurrentSurfaceFromScope($scope.activeSurfaceProfile);
                $scope.activeSurfaceProfile = data.activeSurfaceProfile;
                loadSurfaceIntoScope($scope.activeSurfaceProfile, false);
              }
            }
            if (!activeCurveType && $scope.isParamEnabled('smokeDecay') && data.smokeDecayBezier && typeof data.smokeDecayBezier === 'object') {
              if (Array.isArray(data.smokeDecayBezier)) {
                if (data.smokeDecayBezier.length >= 6) {
                  $scope.smokeDecayBezier = {
                    duration: numOr(data.smokeDecayBezier[0], 1.50),
                    y0: numOr(data.smokeDecayBezier[1], 1.00),
                    x1: numOr(data.smokeDecayBezier[2], 0.25),
                    y1: numOr(data.smokeDecayBezier[3], 0.95),
                    x2: numOr(data.smokeDecayBezier[4], 0.65),
                    y2: numOr(data.smokeDecayBezier[5], 0.15)
                  };
                } else if (data.smokeDecayBezier.length >= 5) {
                  $scope.smokeDecayBezier = {
                    duration: numOr(data.smokeDecayBezier[0], 1.50),
                    y0: 1.00,
                    x1: numOr(data.smokeDecayBezier[1], 0.25),
                    y1: numOr(data.smokeDecayBezier[2], 0.95),
                    x2: numOr(data.smokeDecayBezier[3], 0.65),
                    y2: numOr(data.smokeDecayBezier[4], 0.15)
                  };
                }
              } else if (data.smokeDecayBezier.duration !== undefined) {
                $scope.smokeDecayBezier = Object.assign({ duration: 1.50, y0: 1.00, x1: 0.25, y1: 0.95, x2: 0.65, y2: 0.15 }, data.smokeDecayBezier);
              }
            }
            if ($scope.isParamEnabled('sandDustScale') && Number.isFinite(Number(data.sandDustScale))) $scope.sandDustScale = Number(data.sandDustScale);
            if ($scope.isParamEnabled('sandDustSens') && Number.isFinite(Number(data.sandDustSens))) $scope.sandDustSens = Number(data.sandDustSens);
            if (data.sandDustEnabled !== undefined) $scope.sandDustEnabled = !!data.sandDustEnabled;
            if (data.asphaltSmokeEnabled !== undefined) $scope.asphaltSmokeEnabled = !!data.asphaltSmokeEnabled;
            const ueVal = (data.underbodyEject !== undefined) ? data.underbodyEject : data.wakeShielding;
            if ($scope.isParamEnabled('underbodyEject') && Number.isFinite(Number(ueVal))) $scope.underbodyEject = Number(ueVal);
            if ($scope.isParamEnabled('archEject') && Number.isFinite(Number(data.archEject))) $scope.archEject = Number(data.archEject);
            if ($scope.isParamEnabled('vorticityStrength') && Number.isFinite(Number(data.vorticityStrength))) $scope.vorticityStrength = Number(data.vorticityStrength);
            if ($scope.isParamEnabled('roadDamping') && Number.isFinite(Number(data.roadDamping))) $scope.roadDamping = Number(data.roadDamping);
            if ($scope.isParamEnabled('smokeDrag') && Number.isFinite(Number(data.smokeDrag))) $scope.smokeDrag = Number(data.smokeDrag);
            if ($scope.isParamEnabled('slipstream') && Number.isFinite(Number(data.slipstream))) $scope.slipstream = Number(data.slipstream);
            if ($scope.isParamEnabled('slipstreamSpeedLimit') && Number.isFinite(Number(data.slipstreamSpeedLimit))) $scope.slipstreamSpeedLimit = Number(data.slipstreamSpeedLimit);
            if ($scope.isParamEnabled('slipstreamHoldTime') && Number.isFinite(Number(data.slipstreamHoldTime))) $scope.slipstreamHoldTime = Number(data.slipstreamHoldTime);
            if (data.slipstreamBezier && typeof data.slipstreamBezier === 'object') {
              if (Array.isArray(data.slipstreamBezier) && data.slipstreamBezier.length >= 4) {
                $scope.slipstreamBezier = {
                  x1: numOr(data.slipstreamBezier[0], 1.0),
                  y1: numOr(data.slipstreamBezier[1], 1.0),
                  x2: numOr(data.slipstreamBezier[2], 1.0),
                  y2: numOr(data.slipstreamBezier[3], 0.0)
                };
              } else if (data.slipstreamBezier.x1 !== undefined) {
                $scope.slipstreamBezier = Object.assign({}, data.slipstreamBezier);
              }
            }
            if (!activeCurveType && $scope.isParamEnabled('smokeOnset') && data.smokeOnsetBezier && typeof data.smokeOnsetBezier === 'object') {
              if (Array.isArray(data.smokeOnsetBezier)) {
                if (data.smokeOnsetBezier.length >= 8) {
                  $scope.smokeOnsetBezier = {
                    x0: Number.isFinite(Number(data.smokeOnsetBezier[0])) ? Number(data.smokeOnsetBezier[0]) : 70,
                    y0: Number.isFinite(Number(data.smokeOnsetBezier[1])) ? Number(data.smokeOnsetBezier[1]) : 0.0,
                    x1: Number.isFinite(Number(data.smokeOnsetBezier[2])) ? Number(data.smokeOnsetBezier[2]) : 0.25,
                    y1: Number.isFinite(Number(data.smokeOnsetBezier[3])) ? Number(data.smokeOnsetBezier[3]) : 0.05,
                    x2: Number.isFinite(Number(data.smokeOnsetBezier[4])) ? Number(data.smokeOnsetBezier[4]) : 0.55,
                    y2: Number.isFinite(Number(data.smokeOnsetBezier[5])) ? Number(data.smokeOnsetBezier[5]) : 0.95,
                    x3: Number.isFinite(Number(data.smokeOnsetBezier[6])) ? Number(data.smokeOnsetBezier[6]) : 220,
                    y3: Number.isFinite(Number(data.smokeOnsetBezier[7])) ? Number(data.smokeOnsetBezier[7]) : 1.00
                  };
                } else if (data.smokeOnsetBezier.length >= 6) {
                  $scope.smokeOnsetBezier = {
                    x0: numOr(data.smokeOnsetBezier[0], 70),
                    y0: numOr(data.smokeOnsetBezier[1], 0.0),
                    x1: numOr(data.smokeOnsetBezier[2], 0.25),
                    y1: numOr(data.smokeOnsetBezier[3], 0.05),
                    x2: numOr(data.smokeOnsetBezier[4], 0.55),
                    y2: numOr(data.smokeOnsetBezier[5], 0.95),
                    x3: 220,
                    y3: 1.00
                  };
                } else if (data.smokeOnsetBezier.length >= 4) {
                  $scope.smokeOnsetBezier = {
                    x0: 70,
                    y0: 0.0,
                    x1: numOr(data.smokeOnsetBezier[0], 0.25),
                    y1: numOr(data.smokeOnsetBezier[1], 0.05),
                    x2: numOr(data.smokeOnsetBezier[2], 0.55),
                    y2: numOr(data.smokeOnsetBezier[3], 0.95),
                    x3: 220,
                    y3: 1.00
                  };
                }
              } else if (data.smokeOnsetBezier.x1 !== undefined) {
                $scope.smokeOnsetBezier = Object.assign({ x0: 70, y0: 0.0, x3: 220, y3: 1.00 }, data.smokeOnsetBezier);
              }
            }
            if ($scope.isParamEnabled('slipstreamTurbScale') && Number.isFinite(Number(data.slipstreamTurbScale))) $scope.slipstreamTurbScale = Number(data.slipstreamTurbScale);
            if ($scope.isParamEnabled('slipstreamTurbStrength') && Number.isFinite(Number(data.slipstreamTurbStrength))) $scope.slipstreamTurbStrength = Number(data.slipstreamTurbStrength);
            if ($scope.isParamEnabled('coreLifetime') && Number.isFinite(Number(data.coreLifetime))) $scope.coreLifetime = Number(data.coreLifetime);
            if ($scope.isParamEnabled('thermalBuoyancy') && Number.isFinite(Number(data.thermalBuoyancy))) $scope.thermalBuoyancy = Number(data.thermalBuoyancy);
            if ($scope.isParamEnabled('treadSaturation') && Number.isFinite(Number(data.treadSaturation))) $scope.treadSaturation = Number(data.treadSaturation);
            if ($scope.isParamEnabled('treadCoupling') && Number.isFinite(Number(data.treadCoupling))) $scope.treadCoupling = Number(data.treadCoupling);
            if ($scope.isParamEnabled('edgeDispersion') && Number.isFinite(Number(data.edgeDispersion))) $scope.edgeDispersion = Number(data.edgeDispersion);
            if ($scope.isParamEnabled('dispersionRate') && Number.isFinite(Number(data.dispersionRate))) $scope.dispersionRate = Number(data.dispersionRate);
            if (Number.isFinite(Number(data.treadTurbulence))) $scope.treadTurbulence = Number(data.treadTurbulence);
            if ($scope.isParamEnabled('turbTransition') && Number.isFinite(Number(data.turbTransition))) $scope.turbTransition = Number(data.turbTransition);
            if ($scope.isParamEnabled('turbRelax') && Number.isFinite(Number(data.turbRelax))) $scope.turbRelax = Number(data.turbRelax);
            if ($scope.isParamEnabled('turbScale1') && Number.isFinite(Number(data.turbScale1))) $scope.turbScale1 = Number(data.turbScale1);
            if ($scope.isParamEnabled('turbStrength1') && Number.isFinite(Number(data.turbStrength1))) $scope.turbStrength1 = Number(data.turbStrength1);
            if ($scope.isParamEnabled('turbScale2') && Number.isFinite(Number(data.turbScale2))) $scope.turbScale2 = Number(data.turbScale2);
            if ($scope.isParamEnabled('turbStrength2') && Number.isFinite(Number(data.turbStrength2))) $scope.turbStrength2 = Number(data.turbStrength2);
            if ($scope.isParamEnabled('turbArch') && Number.isFinite(Number(data.turbArch))) $scope.turbArch = Number(data.turbArch);
            if ($scope.isParamEnabled('turbArchScale') && Number.isFinite(Number(data.turbArchScale))) $scope.turbArchScale = Number(data.turbArchScale);
            if (Number.isFinite(Number(data.microFiber))) $scope.microFiber = Number(data.microFiber);
            if (Number.isFinite(Number(data.fiberScale))) $scope.fiberScale = Number(data.fiberScale);
            if ($scope.isParamEnabled('hazeNormals') && Number.isFinite(Number(data.hazeNormals))) $scope.hazeNormals = Number(data.hazeNormals);
            if ($scope.isParamEnabled('creviceShadow') && Number.isFinite(Number(data.creviceShadow))) $scope.creviceShadow = Number(data.creviceShadow);
            if ($scope.isParamEnabled('coreOpacity') && Number.isFinite(Number(data.coreOpacity))) $scope.coreOpacity = Number(data.coreOpacity);
            if ($scope.isParamEnabled('vorticityDetail') && Number.isFinite(Number(data.vorticityDetail))) $scope.vorticityDetail = Number(data.vorticityDetail);
            if (!data.activeSurfaceProfile || data.activeSurfaceProfile === $scope.activeSurfaceProfile) {
              saveCurrentSurfaceFromScope($scope.activeSurfaceProfile);
            }
            if (data.smokeColor && Array.isArray(data.smokeColor) && data.smokeColor.length >= 3) {
              const r = Number(data.smokeColor[0]);
              const g = Number(data.smokeColor[1]);
              const b = Number(data.smokeColor[2]);
              $scope.smokeColor = [
                Number.isFinite(r) ? Math.max(0, Math.min(1, r)) : 1.0,
                Number.isFinite(g) ? Math.max(0, Math.min(1, g)) : 1.0,
                Number.isFinite(b) ? Math.max(0, Math.min(1, b)) : 1.0
              ];
            }
            if (data.dustColor && Array.isArray(data.dustColor) && data.dustColor.length >= 3) {
              const r = Number(data.dustColor[0]);
              const g = Number(data.dustColor[1]);
              const b = Number(data.dustColor[2]);
              $scope.dustColor = [
                Number.isFinite(r) ? Math.max(0, Math.min(1, r)) : 0.76,
                Number.isFinite(g) ? Math.max(0, Math.min(1, g)) : 0.65,
                Number.isFinite(b) ? Math.max(0, Math.min(1, b)) : 0.50
              ];
            }
            if (Number.isFinite(Number(data.debugWakeMode))) $scope.debugWakeMode = Number(data.debugWakeMode);
          }
        });
      });
    }]
  };
}]);
