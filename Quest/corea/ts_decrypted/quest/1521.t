CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1521;
	title = 152102;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 152109;
				ctype = 1;
				idx = 2971108;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 152108;
				gtype = 0;
				area = 152101;
				goal = 152104;
				grade = 132203;
				rwd = 100;
				sort = 152105;
				stype = 1;
				taid = 1;
				title = 152102;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 152114;
			nextlnk = 254;
			rwdtbl = 152101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3242201;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 152108;
			gtype = 0;
			oklnk = 2;
			area = 152101;
			goal = 152104;
			sort = 152105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 152102;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 152107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 2971108;
			}
			CDboTSCheckLvl
			{
				maxlvl = 56;
				minlvl = 48;
			}
			CDboTSCheckClrQst
			{
				and = "1520;";
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
	}
}

