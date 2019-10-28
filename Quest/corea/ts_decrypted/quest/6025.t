CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6025;
	title = 602502;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 602507;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 8;
			}
			CDboTSClickNPC
			{
				npcidx = 4511201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6008;";
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
				conv = 602509;
				ctype = 1;
				idx = 4511201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 602508;
				gtype = 1;
				area = 602501;
				goal = 602504;
				grade = -1;
				rwd = 100;
				sort = 602505;
				stype = 8;
				taid = 1;
				title = 602502;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 602508;
			gtype = 1;
			oklnk = 2;
			area = 602501;
			goal = 602504;
			sort = 602505;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 602502;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 602514;
			nextlnk = 253;
			rwdtbl = 602501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4511108;
			}
		}
	}
}

