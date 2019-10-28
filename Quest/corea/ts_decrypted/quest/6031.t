CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6031;
	title = 603102;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 603107;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 16;
			}
			CDboTSClickNPC
			{
				npcidx = 4751104;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6009;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;0;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 603109;
				ctype = 1;
				idx = 4751104;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 603108;
				gtype = 1;
				area = 603101;
				goal = 603104;
				grade = -1;
				rwd = 100;
				sort = 603105;
				stype = 8;
				taid = 1;
				title = 603102;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 603108;
			gtype = 1;
			oklnk = 2;
			area = 603101;
			goal = 603104;
			sort = 603105;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 603102;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 603114;
			nextlnk = 253;
			rwdtbl = 603101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4752105;
			}
		}
	}
}

