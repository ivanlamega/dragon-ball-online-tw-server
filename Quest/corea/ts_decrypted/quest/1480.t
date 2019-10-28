CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1480;
	title = 148002;

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
				conv = 148009;
				ctype = 1;
				idx = 1352101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 148008;
				gtype = 2;
				area = 148001;
				goal = 148004;
				grade = 132203;
				rwd = 100;
				sort = 148005;
				stype = 1;
				taid = 1;
				title = 148002;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
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
			cont = 148008;
			gtype = 2;
			oklnk = 2;
			area = 148001;
			goal = 148004;
			sort = 148005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 148002;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 148014;
			nextlnk = 254;
			rwdtbl = 148001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 8755301;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 148007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1352101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 55;
				minlvl = 47;
			}
			CDboTSCheckClrQst
			{
				and = "1478;";
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
	}
}

