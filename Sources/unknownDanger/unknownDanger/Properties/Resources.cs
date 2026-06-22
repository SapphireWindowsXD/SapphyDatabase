using System;
using System.CodeDom.Compiler;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Globalization;
using System.Resources;
using System.Runtime.CompilerServices;

namespace unknownDanger.Properties
{
	// Token: 0x02000009 RID: 9
	[GeneratedCode("System.Resources.Tools.StronglyTypedResourceBuilder", "17.0.0.0")]
	[DebuggerNonUserCode]
	[CompilerGenerated]
	internal class Resources
	{
		// Token: 0x06000096 RID: 150 RVA: 0x000042CB File Offset: 0x000024CB
		internal Resources()
		{
		}

		// Token: 0x17000002 RID: 2
		// (get) Token: 0x06000097 RID: 151 RVA: 0x000042D8 File Offset: 0x000024D8
		[EditorBrowsable(EditorBrowsableState.Advanced)]
		internal static ResourceManager ResourceManager
		{
			get
			{
				bool flag = Resources.resourceMan == null;
				if (flag)
				{
					ResourceManager resourceManager = new ResourceManager("unknownDanger.Properties.Resources", typeof(Resources).Assembly);
					Resources.resourceMan = resourceManager;
				}
				return Resources.resourceMan;
			}
		}

		// Token: 0x17000003 RID: 3
		// (get) Token: 0x06000098 RID: 152 RVA: 0x00004320 File Offset: 0x00002520
		// (set) Token: 0x06000099 RID: 153 RVA: 0x00004337 File Offset: 0x00002537
		[EditorBrowsable(EditorBrowsableState.Advanced)]
		internal static CultureInfo Culture
		{
			get
			{
				return Resources.resourceCulture;
			}
			set
			{
				Resources.resourceCulture = value;
			}
		}

		// Token: 0x17000004 RID: 4
		// (get) Token: 0x0600009A RID: 154 RVA: 0x00004340 File Offset: 0x00002540
		internal static Bitmap _3dgifmaker28930
		{
			get
			{
				object @object = Resources.ResourceManager.GetObject("3dgifmaker28930", Resources.resourceCulture);
				return (Bitmap)@object;
			}
		}

		// Token: 0x17000005 RID: 5
		// (get) Token: 0x0600009B RID: 155 RVA: 0x00004370 File Offset: 0x00002570
		internal static Bitmap wnoise
		{
			get
			{
				object @object = Resources.ResourceManager.GetObject("wnoise", Resources.resourceCulture);
				return (Bitmap)@object;
			}
		}

		// Token: 0x04000034 RID: 52
		private static ResourceManager resourceMan;

		// Token: 0x04000035 RID: 53
		private static CultureInfo resourceCulture;
	}
}
