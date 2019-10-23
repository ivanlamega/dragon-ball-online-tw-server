CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6028;
	title = 602802;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 602807;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 8;
			}
			CDboTSClickNPC
			{
				npcidx = 5553102;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6027;";
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
				conv = 602809;
				ctype = 1;
				idx = 5553102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 602808;
				gtype = 1;
				area = 602801;
				goal = 602804;
				grade = -1;
				rwd = 100;
				sort = 602805;
				stype = 8;
				taid = 1;
				title = 602802;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 602808;
			gtype = 1;
			oklnk = 2;
			area = 602801;
			goal = 602804;
			sort = 602805;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 602802;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 602814;
			nextlnk = 253;
			rwdtbl = 602801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4851101;
			}
		}
	}
}

