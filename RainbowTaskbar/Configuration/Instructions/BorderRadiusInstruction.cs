﻿using System.Dynamic;
using System.Runtime.Serialization;
using System.Threading;
using Newtonsoft.Json.Linq;

namespace RainbowTaskbar.Configuration.Instructions;

[DataContract]
internal class BorderRadiusInstruction : Instruction {
    [field: DataMember] public int Radius { get; set; } = 0;

    public override bool Execute(Taskbar window, CancellationToken _) {
        window.taskbarHelper.Radius = Radius;
        window.windowHelper.Radius = Radius;

        return false;
    }

    public override JObject ToJSON() {
        dynamic data = new ExpandoObject();
        data.Name = GetType().Name;
        data.Radius = Radius;

        return JObject.FromObject(data);
    }
}