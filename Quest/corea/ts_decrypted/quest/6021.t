CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6021;
	title = 602102;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 602107;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 3181301;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6020;";
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
				conv = 602109;
				ctype = 1;
				idx = 3181301;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 602108;
				gtype = 0;
				area = 602101;
				goal = 602104;
				grade = -1;
				rwd = 100;
				sort = 602105;
				stype = 8;
				taid = 1;
				title = 602102;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 602108;
			gtype = 0;
			oklnk = 2;
			area = 602101;
			goal = 602104;
			sort = 602105;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 602102;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 602114;
			nextlnk = 253;
			rwdtbl = 602101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3332301;
			}
		}
	}
}

