CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6027;
	title = 602702;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 602709;
				ctype = 1;
				idx = 4511108;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 602708;
				gtype = 1;
				area = 602701;
				goal = 602704;
				grade = -1;
				rwd = 100;
				sort = 602705;
				stype = 8;
				taid = 1;
				title = 602702;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "0;1;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 602707;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 8;
			}
			CDboTSClickNPC
			{
				npcidx = 4511108;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6026;";
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 602714;
			nextlnk = 253;
			rwdtbl = 602701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5553102;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 602708;
			gtype = 1;
			oklnk = 2;
			area = 602701;
			goal = 602704;
			sort = 602705;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 602702;
		}
	}
}

